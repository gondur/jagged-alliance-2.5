#ifndef __SOUNDMAN_
#define __SOUNDMAN_

#include "types.h"
#include "mss.h"

#ifdef __cplusplus
extern "C" {
#endif

	// Sample status flags
#define		SAMPLE_ALLOCATED			0x00000001
#define		SAMPLE_LOCKED					0x00000002
#define		SAMPLE_RANDOM					0x00000004
#define		SAMPLE_RANDOM_MANUAL	0x00000008


// Sound error values (they're all the same)
#define		NO_SAMPLE							0xffffffff
#define		SOUND_ERROR						0xffffffff

// Maximum allowable priority value
#define		PRIORITY_MAX					0xfffffffe
#define		PRIORITY_RANDOM				PRIORITY_MAX-1

// Struct definition for sample slots in the cache
//		Holds the regular sample data, as well as the
//		data for the random samples

typedef struct {
				CHAR8				pName[128];						// Path to sample data
				UINT32			uiSize;								// Size of sample data
				UINT32			uiSoundSize;					// Playable sound size
				UINT32			uiFlags;							// Status flags
				UINT32			uiSpeed;							// Playback frequency
				BOOLEAN			fStereo;							// Stereo/Mono
				UINT8				ubBits;								// 8/16 bits
				PTR					pData;								// pointer to sample data memory		
				PTR					pSoundStart;					// pointer to start of sound data	
				UINT32			uiCacheHits;

				UINT32			uiTimeNext;						// Random sound data
				UINT32			uiTimeMin, uiTimeMax;
				UINT32			uiSpeedMin, uiSpeedMax;
				UINT32			uiVolMin, uiVolMax;
				UINT32			uiPanMin, uiPanMax;
				UINT32			uiPriority;
				UINT32			uiInstances;
				UINT32			uiMaxInstances;

				UINT32			uiAilWaveFormat;			// AIL wave sample type
				UINT32			uiADPCMBlockSize;			// Block size for compressed files
				UINT8				Reserved[56];					// extra space
				} SAMPLETAG;

// Structure definition for slots in the sound output
//		These are used for both the cached and double-buffered
//		streams
typedef struct {
				SAMPLETAG		*pSample;
				UINT32			uiSample;
				HSAMPLE			hMSS;
				HSTREAM			hMSSStream;
				UINT32			uiFlags;
				UINT32			uiSoundID;
				UINT32			uiPriority;
				void				(*pCallback)(UINT8*, UINT32, UINT32, UINT32, void *);
				void				*pData;
				void				(*EOSCallback)(void *);
				void				*pCallbackData;
				UINT32			uiTimeStamp;
				BOOLEAN			fLooping;
				HWFILE			hFile;
				} SOUNDTAG;

// Structure definition for sound parameters being passed down to
//		the sample playing function
typedef struct {
				UINT32			uiSpeed;
				UINT32			uiPitchBend;					// Random pitch bend range +/-
				UINT32			uiVolume;
				UINT32			uiPan;
				UINT32			uiLoop;
				UINT32			uiPriority;
				void				(*EOSCallback)(void *);
				void				*pCallbackData;
				} SOUNDPARMS;

// Structure definition for parameters to the random sample playing
//		function
typedef struct {
				UINT32			uiTimeMin, uiTimeMax;
				UINT32			uiSpeedMin, uiSpeedMax;
				UINT32			uiVolMin, uiVolMax;
				UINT32			uiPanMin, uiPanMax;
				UINT32			uiPriority;
				UINT32			uiMaxInstances;
				} RANDOMPARMS;

// Structure for the header of a WAV file. This actually contains
//		two separate chunks, but we're not fussy

// NOT USED ANY MORE, OBSOLETE AND INCORRECT ANYWAY!

/*
typedef struct {
				// WAV header
				CHAR8				cRiff[4];				// "RIFF"
				UINT32			uiHeaderSize;		// Chunk length
				CHAR8				cFileType[4];		// "WAVE"

				// FMT chunk				
				CHAR8				cFormat[4];			// "FMT"
				UINT32			uiFormatSize;		// Chunk length
				UINT16			uiStereo;				// 1 if stereo, 0 if mono
				UINT16			uiChannels;			// number of channels used
				UINT32			uiSpeed;				// Sampling Rate (speed)
				UINT32			uiBytesSec;			// Number of bytes per sec
				UINT16			uiBytesSample;	// Number of bytes per sample (1 = 8 bit mono,
																		// 2 = 8 bit stereo or 16 bit mono, 4 = 16 bit stereo
				UINT16			uiBitsSample;		// bits per sample

				// Data chunk
				CHAR8				cName[4];				// "DATA"
				UINT32			uiDataSize;			// Chunk length

				} WAVHEADER;
*/

// Global startup/shutdown functions
extern BOOLEAN	InitializeSoundManager(void);
extern void			ShutdownSoundManager(void);

// Configuration functions
extern BOOLEAN	SoundSetMemoryLimit(UINT32 uiLimit);
extern BOOLEAN	SoundSetCacheThreshhold(UINT32 uiThreshold);
extern HDIGDRIVER SoundGetDriverHandle(void);

// Master volume control functions
extern BOOLEAN	SoundSetDigitalVolume(UINT32 uiVolume);
extern UINT32		SoundGetDigitalVolume(UINT32 uiVolume);

// Cache control functions
extern UINT32		SoundLoadSample(STR pFilename);
extern UINT32		SoundFreeSample(STR pFilename);
extern UINT32		SoundLockSample(STR pFilename);
extern UINT32		SoundUnlockSample(STR pFilename);
extern BOOLEAN	SoundEmptyCache(void);
extern BOOLEAN	SoundSampleIsInUse(UINT32 uiSample);

// Play/service sample functions
extern UINT32		SoundPlay(STR pFilename, SOUNDPARMS *pParms);
extern UINT32		SoundPlayStreamedFile( STR pFilename, SOUNDPARMS *pParms );

extern UINT32		SoundPlayRandom(STR pFilename, RANDOMPARMS *pParms);
extern BOOLEAN	SoundRandomShouldPlay(UINT32 uiSample);
extern UINT32		SoundStartRandom(UINT32 uiSample);
extern UINT32		SoundStreamCallback(STR pFilename, SOUNDPARMS *pParms, void (*pCallback)(UINT8 *, UINT32, UINT32, UINT32, void *), void *);
extern BOOLEAN	SoundServiceStreams(void);
extern BOOLEAN	SoundServiceRandom(void);
extern void			SoundSampleSetVolumeRange(UINT32 uiSample, UINT32 uiVolMin, UINT32 uiVolMax);
extern void			SoundSampleSetPanRange(UINT32 uiSample, UINT32 uiPanMin, UINT32 uiPanMax);

// Sound instance manipulation functions
extern BOOLEAN	SoundStopAll(void);
extern BOOLEAN	SoundStopAllRandom(void);
extern BOOLEAN	SoundStop(UINT32 uiSoundID);
extern BOOLEAN	SoundIsPlaying(UINT32 uiSoundID);
extern BOOLEAN	SoundSetVolume(UINT32 uiSoundID, UINT32 uiVolume);
extern BOOLEAN	SoundSetPan(UINT32 uiSoundID, UINT32 uiPan);
extern BOOLEAN	SoundSetFrequency(UINT32 uiSoundID, UINT32 uiFreq);
extern BOOLEAN	SoundSetLoop(UINT32 uiSoundID, UINT32 uiLoop);
extern UINT32		SoundGetVolume(UINT32 uiSoundID);
extern UINT32		SoundGetPan(UINT32 uiSoundID);
extern UINT32		SoundGetFrequency(UINT32 uiSoundID);
extern UINT32		SoundGetLoop(UINT32 uiSoundID);
extern UINT32		SoundGetPosition(UINT32 uiSoundID);
extern BOOLEAN		SoundGetMilliSecondPosition(UINT32 uiSoundID, UINT32 *puiTotalMilliseconds, UINT32 *puiCurrentMilliseconds);

// Sound instance group functions
extern BOOLEAN	SoundStopGroup(UINT32 uiPriority);
extern BOOLEAN	SoundFreeGroup(UINT32 uiPriority);

extern void SoundSetSampleFlags( UINT32 uiSample, UINT32 uiFlags );
extern void SoundRemoveSampleFlags( UINT32 uiSample, UINT32 uiFlags );

extern void SoundEnableSound(BOOLEAN fEnable);

#ifdef __cplusplus
}
#endif

#endif