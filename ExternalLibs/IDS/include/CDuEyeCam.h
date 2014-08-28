/*!
 * \file    CDuEyeCam.h
 * \date    31.10.2012
 * \author  IDS - Imaging Development Systems GmbH
 */
class CuEyeCam : public CWnd
{
protected:
	DECLARE_DYNCREATE(CuEyeCam)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xa88f30fe, 0x4c03, 0x4e37, { 0xb6, 0xe4, 0xed, 0x93, 0x41, 0x9, 0x37, 0x80 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attribute
public:
	BOOL GetLiveAtStartup();
	void SetLiveAtStartup(BOOL);
	BOOL GetActivate1stCamera();
	void SetActivate1stCamera(BOOL);
	BOOL GetAllowPopupMenu();
	void SetAllowPopupMenu(BOOL);
	BOOL GetEnableErrorReport();
	void SetEnableErrorReport(BOOL);
	BOOL GetEnableBadPixelCorrection();
	void SetEnableBadPixelCorrection(BOOL);
	long GetInitBrightness();
	void SetInitBrightness(long);
	long GetInitContrast();
	void SetInitContrast(long);
	long GetInitGamma();
	void SetInitGamma(long);
	BOOL GetInitFitToWindow();
	void SetInitFitToWindow(BOOL);
	BOOL GetTransferFailedSound();
	void SetTransferFailedSound(BOOL);
	BOOL GetEnableEvents();
	void SetEnableEvents(BOOL);
	BOOL GetEnableColorCorrection();
	void SetEnableColorCorrection(BOOL);
	long GetSequenceLength();
	void SetSequenceLength(long);
	BOOL GetDisplayEnable();
	void SetDisplayEnable(BOOL);
	BOOL GetEnableDirectDraw();
	void SetEnableDirectDraw(BOOL);
    BOOL GetEnableDirect3D();
    void SetEnableDirect3D(BOOL);
	unsigned long GetDDKeyColor();
	void SetDDKeyColor(unsigned long);
	BOOL GetEnableMaxExposure();
	void SetEnableMaxExposure(BOOL);
	BOOL GetEnableVerticalFlipping();
	void SetEnableVerticalFlipping(BOOL);
	BOOL GetEnableHorizontalFlipping();
	void SetEnableHorizontalFlipping(BOOL);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);

// Operationen
public:
	void AboutBox();
	long InitCamera(long hb);
	void ExitCamera();
	long FreezeImage(long timeout);
	long StartLiveVideo(long nMode);
	long StartLiveVideoWait(long nTimeout);
	long StopLiveVideo(long nWait);
	long GetRenderMode();
	long SetRenderMode(long nMode);
	long GetColorMode();
	long SetColorMode(long nMode);
	long GetBrightness();
	long SetBrightness(long nBrightness);
	long GetContrast();
	long SetContrast(long nContrast);
	long GetGamma();
	long SetGamma(long nGamma);
	long GetRopEffect();
	long SetRopEffect(long nEffect, long nParam);
    long GetSaturationU();
    long GetSaturationV();
    long SetSaturation(long nChromU, long nChromV);
	long IsSupportedCPUIdleStatesBattery();
	long IsSupportedCPUIdleStatesMains();
	long IsSupportedOpenMP();
	long GetEnableOpenMPDefault();
	long IsSupportedInitialParameterset();
	CString ReadEEProm();
	long WriteEEProm(LPCTSTR pcString);
	long SaveImage(LPCTSTR strFileName);
	long GetError();
	CString GetErrorText();
	long IsErrorReportEnabled();
	long SetErrorReport(long nMode);

	long GetEdgeEnhancement();
	long SetEdgeEnhancement(long nEnable);
	long GetColorCorrection();
	long SetColorCorrection(long nMode);
	long IsColorCorrectionEnabled();
	long GetBlOffset();
	long SetBlCompensation(long nEnable, long nOffset);
	long IsBlCompensationEnabled();
	long GetCameraHandle();

	/* hotpixel */
	long GetBadPixelCorrection();
	long GetBadPixelThreshold();
	long SetBadPixelCorrection(long nEnable, long nTreshold);
	long IsHardwareBPCEnabled();
	long IsSoftwareBPCEnabled();
	long LoadBPCTable(LPCTSTR FILE);
	long GetDC();
	long ReleaseDC(long hDC);

	long PropertyDialog();
	long HasVideoStarted();
	long IsVideoFinish();
	long GetDLLVersion();
	long GetControlVersion();
	long GetOSVersion();
	long GetCameraType();
	long GetSensorType();
	CString GetSerialNumber();
	CString GetCameraVersion();
	long GetCameraStatus(long nInfo);
	long GetCameraID();
    long GetDeviceID();
	double GetFramesPerSecond();
	long EnableEvent(long nWhich, long bEnable);

	void UpdateDisplay();
	long GetNumberOfCameras();

	CString GetSensorName();
	long SetCameraId(long lid);

	long StealVideo(long lWait);
	long LoadParameters(LPCTSTR strFileName);
	long SaveParameters(LPCTSTR strFileName);	
    long CopyImage(ULONGLONG pBuffer, long lSize);

	long SetViewWindow (OLE_HANDLE WindowHandle);

    long GetDuration (long nMode, long *pnTime);

	long SaveImageEx (LPCSTR strFileName, long fileFormat, long Param);
	long GetUsedBandwidth (void);
	long ClearDirect3DOverlay (void);
	long ReadI2C (long nDeviceAddr, long nRegisterAddr, BYTE* pdDATA, long nLen);
	long WriteI2C (long nDeviceAddr, long nRegisterAddr, BYTE* pbData, long nLen);
	long GetCameraLUT (unsigned long Mode, unsigned long NumberOfEntries, double* pRed_Grey, double* pGreen, double* pBlue);
 	long GetColorConverter (long ColorMode, long* pCurrentConvertMode, long* pDefaultConvertMode, long* pSupportedConvertModes);
	long GetSupportedTestImages (long* SupportedTestImages);
	long EnableHdr (long Enable);
	long GetComportNumber (unsigned long* pComportNumber);
	long GetHdrMode (long* Mode);
	VARIANT GetImageHistogram (long ColorMode);
	long ResetCaptureErrorInfo (void);
	BOOL IsMemoryBoardConnected();
	long SetCameraLUT (unsigned long Mode, unsigned long NumberOfEntries, double* pRed_Grey, double* pGreen, double* pBlue);
	long SetColorConverter (long ColorMode, long ConvertMode);
	long SetGlobalShutter (long mode);

	long SetOptimalCameraTiming (long Mode, long Timeout_, long* pMaxPxlClk, double* pMaxFrameRate);
	long SetSensorTestImage (long TestImage, long Param);

	long GetTestImageValueRange (long TestImage, long* TestImageValueMin, long* TestImageValueMax);

	long GetColorDepth (long* pnCol, long* pnColMode);
	long ResetToDefault(void);
	long GetBusSpeed(void);

	VARIANT GetCaptureErrorInfo(unsigned long* dwCapErrCnt_Total);

	/* Timing */
	long GetPixelClock();
	long SetPixelClock(long nMhz);
    long GetNumberOfPixelClocks(UINT* nNumber);
	double GetFrameRate();
	double SetFrameRate(double dFps);
	double GetExposureTime();
	double SetExposureTime(double dExp);
    long GetExposureTimeRange(double* minExp, double* maxExp, double* intervall);
	long GetPixelClockRange (long* nMin, long* nMax, long* nDefault);
	long GetFrameTimeRange( double* minFps, double* maxFps, double* intervall);

	/* White balance */
	long GetWhiteBalance();
	long SetWhiteBalance(long nMode);
	long GetWhiteBalanceMultipliers(double* nRed, double* nGreen, double* nBlue);
	long SetWhiteBalanceMultipliers(double nRed, double nGreen, double nBlue);

	/* Memory */
	VARIANT GetImageMem();
	long SetAllocatedImageMem(ULONGLONG pBuffer, long lSize);
	long InquireImageMem(long* nWidth, long* nHeight, long* nBits, long* nPitch);
	long SetMemoryMode(long nCount, long nDelay);
	long GetLastMemorySequence();
	long GetNumberOfMemoryImages(long nSeqID);
	long TransferImage(long nMemID, long nSeqID, long nImgNr);
	long TransferMemorySequence(long nSeqID, long nStartNr, long nCount, long nSeqPos);
	long MemoryFreezeImage(long timeout);

	/* Gain */
	long GetMasterGain();
	long GetRedGain();
	long GetGreenGain();
	long GetBlueGain();
	long SetHardwareGain(long nMaster, long nRed, long nGreen, long nBlue);

	/* Size */
	long GetImageWidth();
	long GetImageHeight();
	long GetImageSize(long* nWidth, long* nHeight);
	long SetImageSize(long nWidth, long nHeight);
	long GetImagePosition(long* xPos, long* yPos);
	long SetImagePosition(long xPos, long yPos);
	long GetBinning();
	long SetBinning(long lMode);
	long GetSubSampling();
	long SetSubSampling(long nMode);
	long SetAOI (long type, long* pXPos, long* pYPos, long* pWidth, long* pHeight);
	long SetImageAOI(long lPosX, long lPosY, long lWidth, long lHeight);

	/* new - IO */
	long IO_GPIO				(unsigned long nCommand, long* pnMode);
	long IO_Flash				(unsigned long nCommand, long* pnMode);
	long IO_Flash_Parameters	(unsigned long nCommand, long* pnDelay, long* pnDuration);
	long IO_PWM					(unsigned long nCommand, long* pnMode);
	long IO_PWM_Parameters		(unsigned long nCommand, double* pdblFrequencey, double* pdblDutyCycle);
	long IO_LED					(unsigned long nCommand, long* pnMode);

	/* old - IO */
	long SetIO(long nIO);
	long GetIO(void);
	long SetIOMask(long nIOMask);
	long GetIOMask(void);
	long SetLED (long nValue);

	/* Hdr kneepoints */
    long AddHDRKneepoint(double dblX, double dblY);
    long SetAtHDRKneepoint(int nPos, double dblX, double dblY);
    long DeleteHDRKneepoint(int nPos);
    long SetHDRKneepointsDefault();
    VARIANT GetHdrKneepoints(void);
    VARIANT GetHdrKneepointInfo(long* NumberOfSupportedKneepoints, double* MinValueX, double* MaxValueX,
							 double* MinValueY, double* MaxValueY);

    // New functions for the uEye XS

    /* Focus */
    BOOL GetEnableAutoFocus();
    void SetEnableAutoFocus(BOOL propVal);
    long GetManualFocus();
    void SetManualFocus(long propVal);
    long GetAutoFocusRange();
    void SetAutoFocusRange(long propVal);
    long GetFocusDistance();
    long GetManualFocusRange(long *pMin, long *pMax, long *pInc);

    /* Face detection */
    BOOL GetEnableFaceDetection();
    void SetEnableFaceDetection(BOOL propVal);
    BOOL GetSuspendFaceDetection();
    void SetSuspendFaceDetection(BOOL propVal);
    VARIANT GetFDTFaceList();
    long GetFDTMaxNumOvl();
    void SetFDTMaxNumOvl(long propVal);
    long GetFDTMaxNumFaces();
    long GetFDTNumberFaces();
    BOOL GetEnableFDTSearchAngle();
    void SetEnableFDTSearchAngle(BOOL propVal);
    long GetFDTSearchAngle();
    void SetFDTSearchAngle(long propVal);
    long GetFDTLineWidthOvl();
    void SetFDTLineWidthOvl(long propVal);
    long GetFDTResolution(unsigned long * pulHorizRes, unsigned long *pulVertRes);

    /* Image format */
    long GetIFFormat();
    void SetIFFormat(long propVal);
    long GetIFNumberFormats();
    VARIANT GetIFFormatList();

    /* Image stabilization */
    BOOL GetEnableImageStabilization();
    void SetEnableImageStabilization(BOOL propVal);

    BOOL IsIFArbitraryAOISupported();

    /* Sensor auto features */
    BOOL GetEnableAutoSensorWB();
    void SetEnableAutoSensorWB(BOOL propVal);
    BOOL GetEnableAutoSensorShutter();
    void SetEnableAutoSensorShutter(BOOL propVal);
    BOOL GetEnableAutoSensorGain();
    void SetEnableAutoSensorGain(BOOL propVal);
    long GetAutoSensorShutterMode();
    void SetAutoSensorShutterMode(long propVal);
    long GetAutoSensorShutterDefault();
    long GetAutoSensorShutterCapabilities();
    long GetAutoSensorGainMode();
    void SetAutoSensorGainMode(long propVal);
    long GetAutoSensorGainDefault();
    long GetAutoSensorGainCapabilities();
    long GetAutoSensorWBMode();
    void SetAutoSensorWBMode(long propVal);
    long GetAutoSensorWBDefault();
    long GetAutoSensorWBCapabilities();

    /* Anti flicker */
    BOOL IsAntiFlickerSupported();
    long GetAntiFlickerMode();
    void SetAntiFlickerMode(long propVal);
    long GetAntiFlickerModeDefault();
    long GetAntiFlickerSupportedModes();
    
    /* Auto backlight compensation */
    BOOL IsAutoBacklightCompSupported();
    BOOL GetEnableAutoBacklightComp();
    void SetEnableAutoBacklightComp(BOOL propVal);
	
    /* Auto contrast correction */
    BOOL IsAutoContrastCorrSupported();
    double GetAutoContrastCorrectionValue();
    void SetAutoContrastCorrectionValue(double propVal);
    double GetAutoContrastCorrectionValueDefault();
    long GetAutoContrastCorrectionRange  (double* pdMin, double* pdMax, double* pdInc);
    
    /* Enable use of FDT AOI for AES/aGC */
    BOOL GetEnableUseFDTAOIforAESAGC();
    void SetEnableUseFDTAOIforAESAGC(BOOL propVal);
    
    /* Scene selection */
    BOOL IsScenePresetSupported(); 
    void SetScenePreset(long propVal);
    long GetScenePreset();
    long GetScenePresetDefault();
    long GetSceneSupportedPresets();
    
    /* Digital zoom */
    BOOL IsDigitalZoomSupported();
    VARIANT GetDigitalZoomSupportedFactors();
    void SetDigitalZoomFactor(double dZoomFactor);
    double GetDigitalZoomFactor();
    
    /* Sharpness correction */
    BOOL IsSharpnessSupported();
    void SetSharpnessValue(long nSharpness);
    long GetSharpnessValue();
    long GetSharpnessValueDefault();
    long GetSharpnessRange(long* pnMin, long* pnMax, long* pnInc);
    
    /* Saturation */
    BOOL IsSaturationSupported();
    void SetSaturationValue(long nSaturation);
    long GetSaturationValue();
    long GetSaturationValueDefault();
    long GetSaturationRange(long* pnMin, long* pnMax, long* pnInc);

    /* RGB color model */
    void SetRGBColorModel(long nColorModel);
    long GetRGBColorModel();
    long GetRGBColorModelDefault();
    long GetRGBColorModelSupportedModels();

    /* Color temperature */
    void SetColorTemperature(long nTemperature);
    long GetColorTemperature();
    long GetColorTemperatureDefault();
    long GetColorTemperatureRange(long* pnMin, long* pnMax, long* pnInc);

	/* Direct renderer */
	long DirectRenderer (long nMode, void *pParam, long SizeOfParam);
    BOOL IsDirectRendererSupported();
	long DRSetHWND(OLE_HANDLE hWnd);
	long DRClearOverlay();
	long DRLoadOverlayFromFile(LPCTSTR strFileName);
	long DRGetSyncUserRange(long * pnMin, long * pnMax);
	long DRSetSyncUser(long nSyncPos);
	long DREnableSyncAuto(BOOL bNewVal);
	long DREnableSemiTransparentOverlay(BOOL bNewVal);
	long DREnableImageScaling();
	long DREnableScaling(BOOL bNewVal);
	long DRShowOverlay(BOOL bNewVal);
	long DRSetOverlayKeyColor(long nRed, long nGreen, long nBlue);
	long DRGetOverlayKeyColor(long * pnRed, long * pnGreen, long * pnBlue);
	long DRSetOverlayPos(long nX, long nY);
	long DRSetOverlaySize(long nWidth, long nHeight);
	long DRGetMaxOverlaySize(long * pnWidth, long * pnHeight);
	long DRReleaseOverlayDC();
	long DRGetOverlayDC(long* hDC);
    void DRSetStealFormat(long nColorFormat);
    long DRGetStealFormat();
    
	/* Flash strobe */
	long GetFlashStrobe();
	long SetFlashStrobe(long nMode);
	unsigned long GetFlashDelay();
	long SetFlashDelay(unsigned long ulDelay);
	long SetGlobalFlashDelays();
	unsigned long GetFlashDuration();
	long SetFlashDuration(unsigned long ulDuration);

	/* Trigger */
    long GetTriggerDelay();
    void SetTriggerDelay(long nDelay);
    long GetTriggerStatus();
	long ForceTrigger();
	BOOL ReadTriggerPort();
	long GetTimeout (unsigned long nMode, unsigned long* pTimeout);
	long SetTimeout (unsigned long nMode, unsigned long Timeout);
	long GetExternalTrigger();
	long SetExternalTrigger(long nMode);

    /* Trigger debouncing */
    void SetTriggerDebounceMode(long nMode);
    long GetTriggerDebounceMode();
    long GetTriggerDebounceModeDefault();
    long GetTriggerDebounceSupportedMode();
    void SetTriggerDebounceDelay(long nDelay);
    long GetTriggerDebounceDelay();
    long GetTriggerDebounceDelayDefault();
    long GetTriggerDebounceDelayRange(long* pnMin, long* pnMax, long* pnInc);

    /* Auto feature functions */
    BOOL GetEnableAutoExposure();	
    void SetEnableAutoExposure(BOOL bNewVal);
    BOOL GetEnableAutoGain();
    void SetEnableAutoGain(BOOL bNewVal);
    BOOL GetEnableAutoFramerate();	
    void SetEnableAutoFramerate(BOOL bNewVal);
    long GetAutoBrightSpeed();
    void SetAutoBrightSpeed(long nSpeed);
    long GetAutoWBSpeed();
    void SetAutoWBSpeed(long nSpeed);
    long GetAutoBrightReference();
    void SetAutoBrightReference(long nReference);
    long GetAutoBrightMaxGain();
    void SetAutoBrightMaxGain(long nMaxGain);
    double GetAutoBrightMaxExp();
    void SetAutoBrightMaxExp(double dblMaxBrightness);
    long GetAutoWBROffset();	
    void SetAutoWBROffset(long nOffset);
    long GetAutoWBBOffset();	
    void SetAutoWBBOffset(long nOffset);
    long GetAutoWBMinGain();	
    void SetAutoWBMinGain(long nMinGain);
    long GetAutoWBMaxGain();	
    void SetAutoWBMaxGain(long nMaxGain);
	
	/* Skipframes */
	long SetAutoSkipframe(long newVal);
	long GetAutoSkipframe();
	long GetAutoSkipframeMinRange();
	long GetAutoSkipframeMaxRange();

	/* Hysteresis */
	long SetAutoHysteresis(long newVal);
	long GetAutoHysteresis();
	long GetAutoHysteresisMinRange();
	long GetAutoHysteresisMaxRange();

	/* Exposure */
	long Exposure(UINT nCommand, double* pdblValue);
	long ExposureRange(UINT nCommand, double* pdblMin, double* pdblMax, double* pdblInc);
	long ExposureSupported(UINT nCommand, UINT* pnCap);

	/* Trigger */
	long Trigger(UINT nCommand, UINT* pnValue);
	long TriggerRange(UINT nCommand, UINT* pnMin, UINT* pnMax, UINT* pnInc);
	long TriggerSupported(UINT nCommand, UINT* pnCap);

	/* EdgeEnhancement */
	long EdgeEnhancement(UINT nCommand, UINT* pnValue);
	long EdgeEnhancementRange(UINT nCommand, UINT* pnMin, UINT* pnMax, UINT* pnInc);

	/* AutoParameter */
	long AutoParameter(UINT nCommand, UINT* pnValue);

	/* PixelClock */
	long PixelClock(UINT nCommand, UINT* pnValue);
	long PixelClockRange(UINT nCommand, UINT* pnMin, UINT* pnMax, UINT* pnInc);
	VARIANT GetPixelClockList(UINT nSizeOfList);

	/* ParameterSet */
	long ParameterSet(UINT nCommand, LPCTSTR strFileName);
	long ParameterSetNumber(UINT nCommand, UINT* pnNumber);

	/* Transfer */
	long Transfer(UINT nCommand, UINT* pnValue);
	long TransferRange(UINT nCommand, UINT* pnMin, UINT* pnMax, UINT* pnInc);

	/* Configuration */
	long Configuration(UINT nCommand, UINT* pnValue);

	/* Hotpixel */
	long HotPixel(UINT nCommand, UINT* pnValue);

	/* AOI */
	long AOI(UINT nCommand, INT* pXPos, INT* pYPos, INT* pWidth, INT* pHeight);
	long AOI_AbsolutePos(UINT nCommand, UINT* pnAbsPos);

	long AOI_MultiAxes(UINT nCommand, UINT* pnX1, UINT* pnX2, UINT* pnX3, UINT* pnX4, UINT* pnY1, UINT* pnY2, UINT* pnY3, UINT* pnY4);
	long AOI_MultiMode(UINT nCommand, UINT* pnMode);

	long AOI_Sequence(UINT nCommand, INT* pnAOIIndex, INT* pnNumberOfCycleRepetitions, INT* pnXPos, INT* pnYPos, double* pdblExpsoure, INT* pnGain, INT* pnDetachImageParameters);
	long AOI_Sequence_NumberOfCycleRepetitons(UINT nCommand, INT* pnIndex, INT* pnValue);
	long AOI_Sequence_PosX(UINT nCommand, INT* pnIndex, INT* pnValue);
	long AOI_Sequence_PosY(UINT nCommand, INT* pnIndex, INT* pnValue);
	long AOI_Sequence_Exposure(UINT nCommand, INT* pnIndex, double* pdblValue);
	long AOI_Sequence_Gain(UINT nCommand, INT* pnIndex, INT* pnValue);
	long AOI_Sequence_DetachImageParameter(UINT nCommand, INT* pnIndex, INT* pnValue);
	long AOI_SequenceMode(UINT nCommand, INT* pnMode);

	/* Convert */
	long Convert(ULONGLONG pSourceBuffer, ULONGLONG pDestBuffer, INT nDestPixelFormat, INT nDestPixelConverter, INT nDestGamma, INT nDestEdgeEnhancement, INT nDestColorCorrectionMode, INT nDestSaturationU, INT nDestSaturationV);

	/* XS(2) Features - Focus */
	long Focus_IsAutoFocusSupported(UINT* piSupported);
	long Focus_SetAutoFocus (BOOL bEnable);
	long Focus_GetAutoFocus (BOOL* pbEnable);
	long Focus_GetAutoFocusStatus (INT* pnStatus);
	long Focus_SetEnableAutoFocusOnce ();
	long Focus_SetManualFocus (UINT uiManual);
	long Focus_GetManualFocus (UINT* puiManual);
	long Focus_GetManualFocusRange (UINT* puiMin, UINT* puiMax, UINT* puiInc);
	long Focus_GetAutoFocusZone (UINT* puiPosX, UINT* puiPosY, UINT* puiWidth, UINT* puiHeight);
	long Focus_SetAutoFocusZone (UINT uiPosX, UINT uiPosY, UINT uiWidth, UINT uiHeight);
	long Focus_GetAutoFocusZoneDefault (UINT* puiPosX, UINT* puiPosY, UINT* puiWidth, UINT* puiHeight);
	long Focus_GetAutoFocusZonePosMin (UINT* puiPosX, UINT* puiPosY);
	long Focus_GetAutoFocusZonePosMax (UINT* puiPosX, UINT* puiPosY);
	long Focus_GetAutoFocusZonePosInc (UINT* puiPosX, UINT* puiPosY);
	long Focus_GetAutoFocusZoneSizeMin (UINT* puiWidth, UINT* puiHeight);
	long Focus_GetAutoFocusZoneSizeMax (UINT* puiWidth, UINT* puiHeight);
	long Focus_GetAutoFocusZoneSizeInc (UINT* puiWidth, UINT* puiHeight);
	long Focus_GetAutoFocusZoneWeight (VARIANT* pviWeight);
	long Focus_SetAutoFocusZoneWeight (VARIANT* pviWeight);
	long Focus_GetAutoFocusZoneWeightDefault (VARIANT* pviWeight);
	long Focus_GetAutoFocusZoneWeightCount (INT* piWeightCount);

	/* XS(2) Features - Image effect */
	long DeviceFeature_GetImageEffectModeDefault (INT* piImageEffect);
 	long DeviceFeature_GetImageEffectMode (INT* piImageEffect);
	long DeviceFeature_SetImageEffectMode (INT iImageEffect);

	/* XS(2) Features - JPEG compression */
	long DeviceFeature_GetJPEGCompressionRange (INT* piMin, INT* piMax, INT* piInc);
 	long DeviceFeature_GetJPEGCompressionDefault (INT* piDefault);
 	long DeviceFeature_GetJPEGCompression (INT* piValue);
 	long DeviceFeature_SetJPEGCompression (INT iValue);

	/* XS(2) Features - Noise reduction */
	long DeviceFeature_GetNoiseReductionModeSupported (BOOL* pbValue);
	long DeviceFeature_GetNoiseReductionModeDefault (INT* piValue);
 	long DeviceFeature_GetNoiseReductionMode (INT* piValue);
	long DeviceFeature_SetNoiseReductionMode (INT iValue);

	/* XS(2) Features - Lens shading model */
 	long ColorTemperature_SetLensShadingModel (UINT uiValue);
 	long ColorTemperature_GetLensShadingModel (UINT* puiValue);
 	long ColorTemperature_GetLensShadingModelSupported (UINT* puiValue);
	long ColorTemperature_GetLensShadingModelDefault (UINT* puiValue);

	/* XS(2) Features - Image format */
	VARIANT ImageFormat_GetList (void);
	long ImageFormat_GetNumberOfEntries (UINT* puiValue);
 	long ImageFormat_SetFormatID (UINT uiValue);
 	long ImageFormat_GetArbitraryAOISupported (UINT* puiValue);

	/* XS(2) Features - ColorConverter */
	long ColorConverter (INT iColorMode, INT iConvertMode);

	long DeviceFeature_GetTemperature (double* pdblValue);
    long DeviceFeature_GetTemperatureSupported (INT* piValue);
};
