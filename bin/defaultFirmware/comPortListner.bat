@echo off
setlocal

for /f "delims=" %%I in ('wmic path Win32_SerialPort get DeviceID^,Caption^,Description^,Name^,ProviderType /format:list ^| find "="') do (
    set "%%I"
)

echo %DeviceID%
echo %Caption%
echo %Description%
echo %Name%
echo %ProviderType%