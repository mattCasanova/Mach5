@echo off

echo Testing Output...
%1 > Out.txt
diff Output.txt Out.txt > diff.txt

for %%i in (diff.txt) do (
  if %%~zi GTR 0 (
    start /MAX cmd /K "%1".exe 
    exit /b -1
  )
)



