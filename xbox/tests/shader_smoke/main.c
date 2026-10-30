/* First console check of xsc-compiled default.frag variants under libxenon.
 *
 * Panels appear one at a time, STAGE_SECONDS apart, and each is logged over
 * UART. The background keeps pulsing, so if it freezes the GPU hung and the
 * newest panel is the suspect. See README.md for what each panel should show.
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <xenos/xe.h>
#include <xenos/xenos.h>
#include <xenos/edram.h>
#include <console/console.h>
#include <ppc/timebase.h>
#include "smoke_shaders.h"

#define STAGE_SECONDS 5
#define NUM_PANELS 4
#define TEX_SIZE 64
#define NUM_PS_CONSTS 40

/* std140 registers of default.frag's uniform block; literals sit above these */
#define C_FOG_PARAMS 0
#define C_FOG_COLOR  1
#define C_CHAN       6
#define C_LIGHT_POS  8
#define C_LIGHT_COL  16
#define C_KCOLOR     24
#define C_ALPHA_REFS 28
#define C_IND_MTX_R0 33
#define C_IND_MTX_R1 36

struct vertex {
	float pos[4];
	float color[4];
	float uv[2];
	float normal[3];
};

static const struct vertex quad[6] = {
	{{-1,  1, 0, 1}, {1, 1, 1, 1}, {0, 0}, {0, 0, 1}},
	{{ 1,  1, 0, 1}, {1, 1, 1, 1}, {1, 0}, {0, 0, 1}},
	{{ 1, -1, 0, 1}, {1, 1, 1, 1}, {1, 1}, {0, 0, 1}},
	{{-1,  1, 0, 1}, {1, 1, 1, 1}, {0, 0}, {0, 0, 1}},
	{{ 1, -1, 0, 1}, {1, 1, 1, 1}, {1, 1}, {0, 0, 1}},
	{{-1, -1, 0, 1}, {1, 1, 1, 1}, {0, 1}, {0, 0, 1}},
};

static const struct XenosVBFFormat vbf = {
	4, {
		{XE_USAGE_POSITION, 0, XE_TYPE_FLOAT4},
		{XE_USAGE_COLOR,    0, XE_TYPE_FLOAT4},
		{XE_USAGE_TEXCOORD, 0, XE_TYPE_FLOAT2},
		{XE_USAGE_TEXCOORD, 1, XE_TYPE_FLOAT3},
	}
};

struct panel {
	const char *name;
	unsigned char *bin;
	const struct smoke_lit *lit;
	int nlit;
	float xform[4];
	float vertex_alpha_ramp;
	struct XenosShader *ps;
};

static struct panel panels[NUM_PANELS] = {
	{"1 texture modulate", ps1_bin, ps1_lit, PS1_NLIT, {0.45f, 0.45f, -0.5f,  0.5f}, 0},
	{"2 lit, fog, alpha",  ps2_bin, ps2_lit, PS2_NLIT, {0.45f, 0.45f,  0.5f,  0.5f}, 0},
	{"3 three stages, 8 lights", ps3_bin, ps3_lit, PS3_NLIT, {0.45f, 0.45f, -0.5f, -0.5f}, 1},
	{"4 indirect, fog",    ps4_bin, ps4_lit, PS4_NLIT, {0.45f, 0.45f,  0.5f, -0.5f}, 0},
};

static float ps_const[NUM_PS_CONSTS][4];

static void set4(int reg, float x, float y, float z, float w)
{
	ps_const[reg][0] = x;
	ps_const[reg][1] = y;
	ps_const[reg][2] = z;
	ps_const[reg][3] = w;
}

/* Fills constants for one panel. Everything moves with t so a frozen panel is
 * obvious. */
static void setup_constants(int panel, float t)
{
	int i;
	float pulse = 0.5f + 0.5f * sinf(t * 2.0f);

	memset(ps_const, 0, sizeof(ps_const));
	set4(C_FOG_PARAMS, 0, 0.5f, 1.0f, 0);
	set4(C_FOG_COLOR, 0.9f, 0.1f, 0.1f, 1);
	set4(C_CHAN + 0, 0.3f + 0.7f * pulse, 1.0f, 0.3f + 0.7f * pulse, 1);
	set4(C_CHAN + 1, 0.15f, 0.15f, 0.15f, 1);
	set4(C_KCOLOR, 0.5f, 0.5f, 0.5f, 1);

	for (i = 0; i < 8; i++) {
		float a = t + (float)i * 0.785398f;
		set4(C_LIGHT_POS + i, cosf(a), sinf(a), 1.0f, 0);
		set4(C_LIGHT_COL + i, i & 1 ? 0.25f : 0.05f, i & 2 ? 0.25f : 0.05f,
		     i & 4 ? 0.25f : 0.05f, 0);
	}
	/* The first four lights are red, green, blue and white for panel 2 */
	if (panel == 1) {
		set4(C_LIGHT_COL + 0, 0.8f, 0, 0, 0);
		set4(C_LIGHT_COL + 1, 0, 0.8f, 0, 0);
		set4(C_LIGHT_COL + 2, 0, 0, 0.8f, 0);
		set4(C_LIGHT_COL + 3, 0.3f, 0.3f, 0.3f, 0);
		set4(C_ALPHA_REFS, 64, 0, 0, 0);
	} else if (panel == 2) {
		set4(C_ALPHA_REFS, 200, 40, 0, 0);
	} else if (panel == 3) {
		float s = 0.15f * sinf(t * 1.5f);
		set4(C_IND_MTX_R0, s, 0, 0, 0);
		set4(C_IND_MTX_R1, 0, s, 0, 0);
	}
}

static struct XenosSurface *make_texture(struct XenosDevice *xe, int kind)
{
	struct XenosSurface *tex =
		Xe_CreateTexture(xe, TEX_SIZE, TEX_SIZE, 1, XE_FMT_8888 | XE_FMT_ARGB, 0);
	unsigned char *tp = Xe_Surface_LockRect(xe, tex, 0, 0, 0, 0, XE_LOCK_WRITE);
	int x, y;

	for (y = 0; y < TEX_SIZE; y++) {
		unsigned int *row = (unsigned int *)(tp + y * tex->wpitch);
		for (x = 0; x < TEX_SIZE; x++) {
			int dx = x - TEX_SIZE / 2, dy = y - TEX_SIZE / 2;
			unsigned int r, g, b, a = 0xFF;

			if (kind == 0) {
				/* orange and white checker, alpha 255 inside a circle */
				int on = ((x >> 3) ^ (y >> 3)) & 1;
				r = 0xFF;
				g = on ? 0xFF : 0x80;
				b = on ? 0xFF : 0x00;
				a = dx * dx + dy * dy < 24 * 24 ? 0xFF : 0x20;
			} else if (kind == 1) {
				/* left to right: blue into yellow */
				r = g = (unsigned int)(x * 255 / (TEX_SIZE - 1));
				b = 255 - r;
			} else {
				/* smooth bumps around 0.5, for the indirect offset */
				r = (unsigned int)(127.5f + 127.5f * sinf((float)x * 0.39f));
				g = (unsigned int)(127.5f + 127.5f * sinf((float)y * 0.39f));
				b = 128;
			}
			row[x] = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
	Xe_Surface_Unlock(xe, tex);
	return tex;
}

int main(void)
{
	struct XenosDevice _xe, *xe = &_xe;
	struct XenosShader *vs;
	struct XenosVertexBuffer *vb;
	struct XenosSurface *tex[3];
	float vs_const[2][4];
	int i, stage = -1;
	uint64_t t0;

	/* A hang must not lose the stage log */
	setvbuf(stdout, NULL, _IONBF, 0);

	xenos_init(VIDEO_MODE_AUTO);
	console_init();
	printf("shader_smoke: xsc-compiled default.frag variants\n");

	Xe_Init(xe);
	Xe_SetRenderTarget(xe, Xe_GetFramebufferSurface(xe));

	vs = Xe_LoadShaderFromMemory(xe, vs_bin);
	Xe_InstantiateShader(xe, vs, 0);
	Xe_ShaderApplyVFetchPatches(xe, vs, 0, &vbf);
	printf("vertex shader loaded\n");
	for (i = 0; i < NUM_PANELS; i++) {
		panels[i].ps = Xe_LoadShaderFromMemory(xe, panels[i].bin);
		Xe_InstantiateShader(xe, panels[i].ps, 0);
		printf("pixel shader %s loaded\n", panels[i].name);
	}

	vb = Xe_CreateVertexBuffer(xe, sizeof(quad));
	memcpy(Xe_VB_Lock(xe, vb, 0, sizeof(quad), XE_LOCK_WRITE), quad, sizeof(quad));
	Xe_VB_Unlock(xe, vb);

	for (i = 0; i < 3; i++)
		tex[i] = make_texture(xe, i);

	edram_init(xe);
	printf("rendering, a panel every %d seconds\n", STAGE_SECONDS);
	console_close();

	t0 = mftb();
	while (1) {
		uint64_t now = mftb();
		float t = (float)((double)(now - t0) / (double)PPC_TIMEBASE_FREQ);
		int want = (int)(t / STAGE_SECONDS);
		unsigned int level;
		int p, l;

		if (want >= NUM_PANELS)
			want = NUM_PANELS - 1;
		if (want != stage) {
			stage = want;
			printf("stage %d: drawing panel %s\n", stage, panels[stage].name);
		}

		level = 0x18 + (unsigned int)(0x20 * (0.5f + 0.5f * sinf(t * 3.0f)));
		Xe_InvalidateState(xe);
		Xe_SetCullMode(xe, 0);
		Xe_SetZEnable(xe, 0);
		Xe_SetZWrite(xe, 0);
		Xe_SetClearColor(xe, 0xFF000000 | level << 8 | level);

		for (p = 0; p <= stage; p++) {
			struct panel *pn = &panels[p];

			memcpy(vs_const[0], pn->xform, sizeof(pn->xform));
			memset(vs_const[1], 0, sizeof(vs_const[1]));
			vs_const[1][0] = pn->vertex_alpha_ramp;
			Xe_SetVertexShaderConstantF(xe, 0, vs_const[0], 2);
			for (l = 0; l < VS_NLIT; l++)
				Xe_SetVertexShaderConstantF(xe, vs_lit[l].reg, vs_lit[l].v, 1);

			setup_constants(p, t);
			Xe_SetPixelShaderConstantF(xe, 0, ps_const[0], NUM_PS_CONSTS);
			for (l = 0; l < pn->nlit; l++)
				Xe_SetPixelShaderConstantF(xe, pn->lit[l].reg, pn->lit[l].v, 1);

			Xe_SetShader(xe, SHADER_TYPE_PIXEL, pn->ps, 0);
			Xe_SetShader(xe, SHADER_TYPE_VERTEX, vs, 0);
			for (l = 0; l < 3; l++)
				Xe_SetTexture(xe, l, tex[l]);
			Xe_SetStreamSource(xe, 0, vb, 0, sizeof(struct vertex) / 4);
			Xe_DrawPrimitive(xe, XE_PRIMTYPE_TRIANGLELIST, 0, 2);
		}

		Xe_Resolve(xe);
		Xe_Sync(xe);
		while (mftb() - now < PPC_TIMEBASE_FREQ / 60)
			;
	}
	return 0;
}
