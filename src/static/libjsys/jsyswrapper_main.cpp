extern void JC_JUTFader_delete(void* fader) {
    delete reinterpret_cast<JUTFader*>(fader);
}

extern void* JC_JUTFader_new(int ul_x, int ul_y, int br_x, int br_y, u32* color) {
    return JKR_NEW JUTFader(ul_x, ul_y, br_x, br_y, JUtility::TColor(*(GXColor*)color));
}

// @unused (necessary for virtual function emmission)
extern int JC_JKRHeap_dump_sort(void* heap) {
    return reinterpret_cast<JKRHeap*>(heap)->dump_sort();
}

// @unused
extern int JC_JKRHeap_check(void* heap) {
    return reinterpret_cast<JKRHeap*>(heap)->check();
}

// @fabricated - necessary for virtuals
extern void JC_JUTResFont_fabricated(void* font) {
    reinterpret_cast<JUTResFont*>(font)->getLeading();
    reinterpret_cast<JUTResFont*>(font)->getFontType();
    reinterpret_cast<JUTResFont*>(font)->getResFont();
}
// @unused
extern int JC_JUTFont_getWidth(void* font) {
    return reinterpret_cast<JUTResFont*>(font)->getWidth();
}

// @unused -- extra hacked for the right weak func emission order
extern int JC_JUTFont_getHeight(void* font) {
    return reinterpret_cast<JUTResFont*>(font)->getHeight();
    return reinterpret_cast<JUTResFont*>(font)->getDescent();
    return reinterpret_cast<JUTResFont*>(font)->getAscent();
}

extern void* JC_JUTDbPrint_getManager() {
    return JUTDbPrint::getManager();
}

extern void JC_JUTDbPrint_setVisible(void* dbprint, BOOL visible) {
    reinterpret_cast<JUTDbPrint*>(dbprint)->setVisible(visible);
}

extern void JC_J2DOrthoGraph_delete(void* orthograph) {
    delete reinterpret_cast<J2DOrthoGraph*>(orthograph);
}

extern void* JC_J2DOrthoGraph_new() {
    return JKR_NEW J2DOrthoGraph();
}

extern void JC_J2DOrthoGraph_setPort(void* orthograph) {
    reinterpret_cast<J2DOrthoGraph*>(orthograph)->setPort();
}

extern void JC_J2DOrthoGraph_setOrtho(void* orthograph, int ul_x, int ul_y, int br_x, int br_y) {
    reinterpret_cast<J2DOrthoGraph*>(orthograph)->setOrtho(JGeometry::TBox2f((f32)ul_x, (f32)ul_y, (f32)ul_x + (f32)br_x, (f32)ul_y + (f32)br_y), -1.0f, 1.0f);
}

extern void* JC_JUTVideo_getManager() {
    return JUTVideo::getManager();
}
extern void JC_JUTVideo_setRenderMode(void* manager, GXRenderModeObj* renderMode) {
    reinterpret_cast<JUTVideo*>(manager)->setRenderMode(renderMode);
}

extern u32 JC_JUTVideo_getFbWidth(void* manager) {
    return reinterpret_cast<JUTVideo*>(manager)->getFbWidth();
}

extern u32 JC_JUTVideo_getEfbHeight(void* manager) {
    return reinterpret_cast<JUTVideo*>(manager)->getEfbHeight();
}

extern void* JC_JKRHeap_alloc(void* heap, u32 size, int align) {
    return reinterpret_cast<JKRHeap*>(heap)->alloc(size, align);
}

extern s32 JC_JKRHeap_resize(void* heap, void* ptr, s32 new_size) {
    return reinterpret_cast<JKRHeap*>(heap)->resize(ptr, new_size);
}

extern void JC_JKRHeap_free(void* heap, void* mem) {
    reinterpret_cast<JKRHeap*>(heap)->free(mem);
}

extern int JC_JKRHeap_dump(void* heap) {
    return reinterpret_cast<JKRHeap*>(heap)->dump();
}

extern u32 JC_JKRHeap_getFreeSize(void* heap) {
    return reinterpret_cast<JKRHeap*>(heap)->getFreeSize();
}

extern s32 JC_JKRHeap_getTotalFreeSize(void* heap) {
    return reinterpret_cast<JKRHeap*>(heap)->getTotalFreeSize();
}

extern size_t JC_JKRHeap_getSize(void* heap, void* mem) {
    return reinterpret_cast<JKRHeap*>(heap)->getSize(mem);
}

extern void* JC__JKRGetSystemHeap() {
    return JKRHeap::getSystemHeap();
}

extern u32 JC__JKRGetMemBlockSize(void* heap, void* ptr) {
    return JKRHeap::getSize(ptr, reinterpret_cast<JKRHeap*>(heap));
}

extern u8 JC_JKRExpHeap_changeGroupID(void* expheap, u8 groupId) {
    return reinterpret_cast<JKRExpHeap*>(expheap)->changeGroupID((u8)groupId);
}

extern void JC_JUTGamePad_read() {
    JUTGamePad::read();
}

extern PADStatus JC_JUTGamePad_getPadStatus(u32 port) {
    return *JUTGamePad::getPadStatus(port);
}

extern u8 JC_JUTGamePad_recalibrate(u32 port) {
    return JUTGamePad::recalibrate(port);
}

extern void JC_JUTConsole_setOutput(void* console, int output) {
    reinterpret_cast<JUTConsole*>(console)->setOutput(output);
}

extern int JC_JUTConsole_getOutput(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->getOutput();
}

extern void JC_JUTConsole_setVisible(void* console, BOOL visible) {
    reinterpret_cast<JUTConsole*>(console)->setVisible(visible);
}

extern int JC_JUTConsole_isVisible(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->isVisible();
}

extern u32 JC_JUTConsole_getHeight(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->getHeight();
}

extern void JC_JUTConsole_setPosition(void* console, int x, int y) {
    reinterpret_cast<JUTConsole*>(console)->setPosition(x, y);
}

extern int JC_JUTConsole_getPositionX(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->getPositionX();
}

extern void JC_JUTConsole_clear(void* console) {
    reinterpret_cast<JUTConsole*>(console)->clear();
}

extern void JC_JUTConsole_scroll(void* console, int scroll) {
    reinterpret_cast<JUTConsole*>(console)->scroll(scroll);
}

extern void JC_JUTConsole_scrollToLastLine(void* console) {
    reinterpret_cast<JUTConsole*>(console)->scrollToLastLine();
}

extern void JC_JUTConsole_scrollToFirstLine(void* console) {
    reinterpret_cast<JUTConsole*>(console)->scrollToFirstLine();
}

extern u32 JC_JUTConsole_getUsedLine(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->getUsedLine();
}

extern int JC_JUTConsole_getLineOffset(void* console) {
    return reinterpret_cast<JUTConsole*>(console)->getLineOffset();
}

extern void JC_JUTConsole_dumpToTerminal(void* console, int lines) {
    reinterpret_cast<JUTConsole*>(console)->dumpToTerminal(lines);
}

extern void* JC_JUTConsoleManager_getManager() {
    return JUTConsoleManager::getManager();
}

extern void JC_JUTConsoleManager_drawDirect(void* manager, int direct) {
    reinterpret_cast<JUTConsoleManager*>(manager)->drawDirect(direct);
}

extern void* JC_JUTException_getManager() {
    return JUTException::getManager();
}

extern void JC_JUTException_enterAllPad(void* manager) {
    reinterpret_cast<JUTException*>(manager)->enterAllPad();
}

extern void JC_JUTException_setPreUserCallback(void* callback) {
    JUTException::setPreUserCallback((JUTErrorHandler)callback);
}

extern void JC_JUTException_setPostUserCallback(void* callback) {
    JUTException::setPostUserCallback((JUTErrorHandler)callback);
}

extern void JC_JUTException_setMapFile(const char* path) {
    JUTException::appendMapFile(path);
}

extern void* JC_JUTException_getConsole() {
    return JUTException::getConsole();
}

extern BOOL JC_JUTException_isEnablePad(void* manager) {
    return reinterpret_cast<JUTException*>(manager)->isEnablePad();
}

extern int JC_JUTException_readPad(void* mgr, u32* trigger, u32* button) {
    return reinterpret_cast<JUTException*>(mgr)->readPad(trigger, button);
}

extern void JC_JUTException_waitTime(u32 time) {
    JUTException::waitTime(time);
}

extern void* JC_JFWDisplay_createManager_0(GXRenderModeObj* renderMode, void* heap, int exfbNumber, int enableAlpha) {
    return JFWDisplay::createManager(renderMode, reinterpret_cast<JKRHeap*>(heap), (JUTXfb::EXfbNumber)exfbNumber, (bool)enableAlpha);
}

extern void JC_JFWDisplay_destroyManager() {
    JFWDisplay::destroyManager();
}

extern void* JC_JFWDisplay_getManager() {
    return JFWDisplay::getManager();
}

extern void JC_JFWDisplay_setGamma(void* manager, int gamma) {
    reinterpret_cast<JFWDisplay*>(manager)->setGamma(gamma);
}

extern void JC_JFWDisplay_setFrameRate(void* manager, u16 framerate) {
    reinterpret_cast<JFWDisplay*>(manager)->setFrameRate(framerate);
}

extern void JC_JFWDisplay_setFader(void* manager, void* fader) {
    reinterpret_cast<JFWDisplay*>(manager)->setFader(reinterpret_cast<JUTFader*>(fader));
}

extern void JC_JFWDisplay_setClearColor(void* manager, GXColor color) {
    reinterpret_cast<JFWDisplay*>(manager)->setClearColor(color);
}

extern void JC_JFWDisplay_beginRender(void* manager) {
    reinterpret_cast<JFWDisplay*>(manager)->beginRender();
}

extern void JC_JFWDisplay_endRender(void* manager) {
    reinterpret_cast<JFWDisplay*>(manager)->endRender();
}

extern void JC_JFWDisplay_endFrame(void* manager) {
    reinterpret_cast<JFWDisplay*>(manager)->endFrame();
}

extern int JC_JFWDisplay_startFadeIn(void* manager, int len) {
    return reinterpret_cast<JFWDisplay*>(manager)->startFadeIn(len);
}

extern int JC_JFWDisplay_startFadeOut(void* manager, int fadeout) {
    return reinterpret_cast<JFWDisplay*>(manager)->startFadeOut(fadeout);
}

extern int JC_JFWDisplay_getEfbWidth(void* manager) {
    return reinterpret_cast<JFWDisplay*>(manager)->getEfbWidth();
}

extern int JC_JFWDisplay_getEfbHeight(void* manager) {
    return reinterpret_cast<JFWDisplay*>(manager)->getEfbHeight();
}

extern void* JC_JFWDisplay_changeToSingleXfb(void* manager, int index) {
    return reinterpret_cast<JFWDisplay*>(manager)->changeToSingleXfb(index);
}

extern void* JC_JFWDisplay_changeToDoubleXfb(void* manager) {
    return reinterpret_cast<JFWDisplay*>(manager)->changeToDoubleXfb();
}

extern void JC_JFWDisplay_clearEfb(void* manager, GXColor color) {
    reinterpret_cast<JFWDisplay*>(manager)->clearEfb(color);
}

extern const GXRenderModeObj* JC_JFWDisplay_getRenderMode(void* manager) {
    return reinterpret_cast<JFWDisplay*>(manager)->getRenderMode();
}

extern void JC_JFWSystem_setMaxStdHeap(int max) {
    JFWSystem::setMaxStdHeap(max);
}

extern void JC_JFWSystem_setSysHeapSize(u32 size) {
    JFWSystem::setSysHeapSize(size);
}

extern void JC_JFWSystem_setFifoBufSize(u32 size) {
    JFWSystem::setFifoBufSize(size);
}

extern void JC_JFWSystem_setAramAudioBufSize(u32 size) {
    JFWSystem::setAramAudioBufSize(size);
}

extern void JC_JFWSystem_setAramGraphBufSize(u32 size) {
    JFWSystem::setAramGraphBufSize(size);
}

extern void JC_JFWSystem_init() {
    JFWSystem::init();
}

extern void* JC_JFWSystem_getSystemHeap() {
    return JFWSystem::getSystemHeap();
}

extern void* JC_JFWSystem_getRootHeap() {
    return JFWSystem::getRootHeap();
}

extern void* JC_JFWSystem_getSystemConsole() {
    return JFWSystem::getSystemConsole();
}

extern void* JC_JUTProcBar_getManager() {
    return JUTProcBar::getManager();
}

extern void JC_JUTProcBar_setVisible(void* procbar, BOOL visible) {
    reinterpret_cast<JUTProcBar*>(procbar)->setVisible(visible);
}

extern void JC_JUTProcBar_setVisibleHeapBar(void* procbar, BOOL visible) {
    reinterpret_cast<JUTProcBar*>(procbar)->setHeapBarVisible(visible);
}

extern int JC_JKRDecomp_checkCompressed(u8* bufp) {
    return JKRDecomp::checkCompressed(bufp);
}

extern void JC_JKRDecomp_decode(u8* comp_bufp, u8* decomp_bufp, u32 decomp_buf_size, u32 skipCount) {
    JKRDecomp::decode(comp_bufp, decomp_bufp, decomp_buf_size, skipCount);
}

extern void* JC__JKRGetResource(const char* resourceName) {
    return JKRGetResource(resourceName);
}

extern void JC__JKRRemoveResource(void* res) {
    JKRRemoveResource(res);
}

extern void JC__JKRDetachResource(void* ptr) {
    JKRDetachResource(ptr);
}

extern void* JC__JKRMountArchive(const char* path, int mount_mode, void* heap, int mount_direction) {
    return JKRMountArchive(path, (JKRArchive::EMountMode)mount_mode, reinterpret_cast<JKRHeap*>(heap), (JKRArchive::EMountDirection)mount_direction);
}

extern CSDIFileEntry* JC__JKRGetResourceEntry_byName(u32 root_name, const char* res_name, void* archive) {
    return static_cast<CSDIFileEntry*>(
        JKRGetResourceEntry_byName(root_name, res_name, reinterpret_cast<JKRArchive*>(archive)));
}

extern void JC_JKRAramHeap_dump(void* heap) {
    reinterpret_cast<JKRAramHeap*>(heap)->dump();
}

extern void* JC_JKRAram_getAramHeap() {
    return JKRAram::getAramHeap();
}

extern void JC_JKRAramArchive_delete(void* aram_archive) {
    delete reinterpret_cast<JKRAramArchive*>(aram_archive);
}

extern void* JC_JKRAramArchive_new() {
    return JKR_NEW JKRAramArchive();
}

extern BOOL JC__JKRMountFixedAramArchive(void* aram_archive, const char* file) {
    return reinterpret_cast<JKRAramArchive*>(aram_archive)->mountFixed(file, JKRArchive::MOUNT_DIRECTION_HEAD);
}

extern void JC__JKRUnmountFixedAramArchive(void* aram_archive) {
    reinterpret_cast<JKRAramArchive*>(aram_archive)->unmountFixed();
}

extern u32 JC_JKRAramArchive_getAramAddress_byName(void* archive, u32 root_name, const char* res_name) {
    return reinterpret_cast<JKRAramArchive*>(archive)->getAramAddress(root_name, res_name);
}

extern void* JC__JKRAllocFromAram(size_t size) {
    return JKRAllocFromAram(size, JKRAramHeap::Head);
}

#pragma force_active on
extern u32 JC_JKRAramBlock_getAddress(void* aramBlock) {
    return reinterpret_cast<JKRAramBlock*>(aramBlock)->getAddress();
}
#pragma force_active reset

extern u8* JC__JKRAramToMainRam_block(void* aramBlock, u8* ramDst, size_t size) {
    return JKRAram::aramToMainRam(reinterpret_cast<JKRAramBlock*>(aramBlock), ramDst, size, 0, EXPAND_SWITCH_DEFAULT, 0, nullptr, -1, nullptr);
}

extern void* JC__JKRMainRamToAram_block(u8* ramAddr, void* aramBlock, size_t size) {
    return JKRAram::mainRamToAram(ramAddr, reinterpret_cast<JKRAramBlock*>(aramBlock), size, EXPAND_SWITCH_DEFAULT, 0, nullptr, -1);
}

extern void* JC__JKRDvdToMainRam_byName(const char* name, u8* buf, JKRExpandSwitch expandSwitch) {
    return JKRDvdRipper::loadToMainRAM(name, buf, expandSwitch, 0, NULL, JKRDvdRipper::ALLOC_DIR_TOP, 0, NULL);
}

extern void JC_JUTAssertion_changeDevice(int device) {
    JUTAssertion::changeDevice(device);
}

extern void JC_JUTAssertion_changeDisplayTime(int displayTime) {
    JUTAssertion::changeDisplayTime(displayTime);
}

extern void* JC_JUTXfb_getManager() {
    return JUTXfb::getManager();
}

extern void JC_JUTXfb_clearIndex(void* manager) {
    reinterpret_cast<JUTXfb*>(manager)->clearIndex();
}
