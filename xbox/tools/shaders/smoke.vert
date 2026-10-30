#version 330 core
layout(location = 0) in vec4 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_uv;
layout(location = 3) in vec3 a_normal;
layout(std140) uniform Vert {
    vec4 u_xform;  /* xy=scale, zw=offset */
    vec4 u_misc;   /* x=vertex alpha ramp */
};
layout(location = 0) out vec4 v_color;
layout(location = 1) out vec2 v_texcoord0;
layout(location = 2) out vec2 v_texcoord1;
layout(location = 3) out vec3 v_normal;
layout(location = 4) out float v_fog_z;
void main() {
    gl_Position = vec4(a_position.xy * u_xform.xy + u_xform.zw, 0.5, 1.0);
    v_color = vec4(a_color.rgb, 1.0 - u_misc.x * a_uv.y);
    v_texcoord0 = a_uv;
    v_texcoord1 = a_uv * 2.0;
    v_normal = a_normal;
    v_fog_z = a_uv.x;
}
