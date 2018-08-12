setlocal

set esptool=%LocalAppData%\Arduino15\packages\Espressif\tools\esptool\da31d9d\esptool.exe

REM Fallback if esptool not found (PATH environment variable or current dir)
IF NOT EXIST %esptool% (
	set esptool=esptool.exe) 
	
set DeviceID=%1

REM If no arguments provided
IF "%~1" == "" (
	REM Search for COM-port
	for /f "delims=" %%I in ('wmic path Win32_SerialPort get DeviceID^,Caption^,Description^,Name^,ProviderType /format:list ^| find "="') do (
		set "%%I"
	)
				
	echo %DeviceID%
	echo %Caption%
	echo %Description%
	echo %Name%
	echo %ProviderType% )

%esptool% ^
    --chip esp32 ^
    --port %DeviceID% ^
    --baud 921600 ^
    --before default_reset ^
    --after hard_reset ^
    write_flash -z ^
    --flash_mode dio ^
    --flash_freq 80m ^
    --flash_size detect ^
    0xe000 ./boot_app0.bin ^
    0x1000 ./bootloader_qio_80m.bin ^
    0x10000 ./defaultFirmware.pde.bin ^
    0x8000 ./defaultFirmware.pde.partitions.bin 