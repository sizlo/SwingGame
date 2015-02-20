:: Batch file used to copy resources to the executable location after a visual studio build
set solutionDir=%1
set targetDir=%2

:: Windows resources
xcopy /Y /E "%solutionDir%WinResources" "%targetDir%"

:: Game data
xcopy /Y /E "%solutionDir%Data" "%targetDir%"