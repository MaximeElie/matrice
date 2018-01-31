@echo off
mode con lines=999 cols=200

:do
	
	cls
	echo.
	echo Appuyez sur une touche pour compiler puis executer le programme.
	timeout /t -1 > nul
	
	if exist inverse_matrice.exe (
	
		cls
	
		echo.
		
		del inverse_matrice.exe

		echo.
		echo.
		echo.
		echo.
	)
	
	cls

	g++ *.h *.cpp -o matrice.exe
	
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