@echo off
mode con lines=999 cols=200

:do
	
	cls
	echo.
	echo Appuyez sur une touche pour compiler puis executer le programme.
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
		start run
	)

goto do