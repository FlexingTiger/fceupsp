#include <pspkernel.h>
#include <pspdebug.h>
#include <stdio.h>
#include <psppower.h>
#include <pspgu.h>

#include "../../types.h"
#include "../../driver.h"
#include "../../fceu.h"
#include "pspvideo.h"
#include "pspinput.h"
#include "pspaudio.h"
#include "vram.h"
#include "file_browser.h"

#define SOUND_ENABLED

/* Define the module info section */
PSP_MODULE_INFO("fceu-psp", 0, 1, 1);

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Sets new HEAP size for PRX (10MB)
PSP_HEAP_SIZE_KB(10 * 1024);

FCEUGI *CurGame = NULL;
int endgame = 0;
void DoFun();
int SetupCallbacks(void);

int main(int argc, char *argv[])
{
	SetupCallbacks();

	sceKernelDcacheWritebackAll();

	scePowerSetClockFrequency(333, 333, 166);

    PSPVideoInit();

    if(!(FCEUI_Initialize())) {
		printf("FCEUltra did not initialize.\n");
		return(0);
	}

	FCEUI_SetVidSystem(0); // 0 - NTSC
	FCEUI_SetGameGenie(0);
	FCEUI_DisableSpriteLimitation(1);
	FCEUI_SetSoundVolume(512);
	FCEUI_SetSoundQuality(0);
	FCEUI_SetLowPass(0);
#ifdef SOUND_ENABLED
	FCEUI_Sound(22050);
#else
	FCEUI_Sound(0);
#endif

#ifdef SOUND_ENABLED
    PSPAudioInit();
#endif

    FCEUGI *tmp;

    for(;;) {
    	if((tmp=FCEUI_LoadGame(file_browser("ms0:/")))) {
    		printf("Game Loaded!\n");
    		CurGame=tmp;
    	}
    	else {
    		printf("Didn't load Game!\n");
    		continue;
    	}

    	PSPInputInitPads();

    	PSPVideoOverrideNESClut();

#ifdef SOUND_ENABLED
    	PSPAudioPlay();
#endif

    	printf("Before main loop\n");
    	while(CurGame) {//FCEUI_CloseGame turns this false
    		DoFun();
    	}

#ifdef SOUND_ENABLED
    	PSPAudioStop();
#endif
    }

#ifdef SOUND_ENABLED
    PSPAudioFinish();
#endif

	sceGuTerm();

	sceKernelExitGame();

	return 0;
}

void FCEUD_Update(uint8 *XBuf, int32 *tmpsnd, int32 ssize)
{
	PSPVideoRenderFrame(XBuf);
	PSPInputReadPad();

	if(endgame) {
		FCEUI_CloseGame();
		CurGame=0;
		endgame = 0;
	}

#ifdef SOUND_ENABLED
	// Create a 768 samples array. Last sample will be used for padding.
	int padcount = 768 - (ssize * 2);
	u16 last_sample = 0;
	u16 s[768];
	int i, j;

	for(i = 0, j = 0; i < ssize; i++, j+=2) {
		s[j] = (u16)tmpsnd[i];
		s[j + 1] = (u16)tmpsnd[i];
		last_sample = (u16)tmpsnd[i];
	}

	for(i = 0, j = 0; i < padcount; i++, j+=2) {
		s[ssize * 2 + j]     = last_sample;
		s[ssize * 2 + j + 1] = last_sample;
	}

	PSPAudioAddSamples(s, 768);
	//printf("Added %d audio samples.\n", ssize);
#endif

}

void DoFun()
{
    uint8 *gfx;
    int32 *sound;
    int32 ssize;

    FCEUI_Emulate(&gfx, &sound, &ssize, 0);
    FCEUD_Update(gfx, sound, ssize);
}

/* Definitions for some platform-dependant FCEU functions */
void FCEUD_PrintError(char *s) {
	printf("Error: %s", s);
}

FILE *FCEUD_UTF8fopen(const char *fn, const char *mode) {
	return(fopen(fn, mode));
}

void FCEUD_GetPalette(uint8 index, uint8 *r, uint8 *g, uint8 *b) {
//	unsigned int* clut = (unsigned int*)(((unsigned int)clut256)|0x40000000);
//
//	*r = clut[index] & 0xFF;
//	*g = clut[index] & 0xFF00 >> 8;
//	*b = clut[index] & 0xFF0000 >> 16;
}

void FCEUD_SetPalette(uint8 index, uint8 r, uint8 g, uint8 b) {
//	unsigned int* clut = (unsigned int*)(((unsigned int)clut256)|0x40000000);
//
//	unsigned int color = ((b<<16)|(g<<8)|(r<<0));
//
//	clut[index]     = color;
//	clut[index+64]  = color;
//	clut[index+128] = color;
//	clut[index+192] = color;
}

void FCEUD_Message(char *s) {
	printf("Message: %s", s);
}

int FCEUD_SendData(void *data, uint32 len) {
	printf("FCEUD_SendData not implemented");
	return(0);
}

void FCEUD_NetworkClose(void) {
	printf("FCEUD_NetworkClose not implemented");
}


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	sceKernelExitGame();
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);

	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

