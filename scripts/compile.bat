@echo off
mode con lines=999 cols=200

cd %~dp0

:do
	
	cls
	echo.
	echo Appuyez sur une touche pour compiler...
	timeout /t -1 > nul
	
	if exist ../bin/matrice.exe (
	
		cls
	
		echo.
		
		del ../bin/matrice.exe

		echo.
		echo.
		echo.
		echo.
	)

	cls

	g++ ../src/*.h ../src/*.cpp -o ../bin/matrice.exe
	
	
	if %ERRORLEVEL% NEQ 0 (
		echo.
		echo.
		echo.
		echo.

		pause
	) else (
		echo.
		
		echo compilation terminee
		
		timeout /t 2 /nobreak > nul
	)

goto do