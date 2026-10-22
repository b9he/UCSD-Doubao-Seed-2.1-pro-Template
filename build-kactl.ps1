param([switch]$Fast)

$ErrorActionPreference = 'Stop'
$projectRoot = $PSScriptRoot
$toolsRoot = Join-Path (Split-Path $projectRoot -Parent) '.tools'
$texBin = Join-Path $toolsRoot 'TinyTeX\bin\windows'
$pdfLatex = Join-Path $texBin 'pdflatex.exe'
$python = 'D:\anaconda3\python.exe'
$unixBin = 'D:\Program Files (x86)\Git\usr\bin'

foreach ($required in @($pdfLatex, $python, (Join-Path $unixBin 'rm.exe'))) {
    if (-not (Test-Path -LiteralPath $required)) { throw "Required tool missing: $required" }
}

$previousEnvironment = @{}
foreach ($name in @('PATH','TEXINPUTS','PYTHONUTF8','PYTHONIOENCODING','max_print_line')) {
    $previousEnvironment[$name] = [Environment]::GetEnvironmentVariable($name, 'Process')
}
Push-Location $projectRoot
try {
    $env:PATH = "$toolsRoot\bin;$texBin;$unixBin;$env:PATH"
    $env:TEXINPUTS = '.;content/tex/;'
    $env:PYTHONUTF8 = '1'
    $env:PYTHONIOENCODING = 'utf-8'
    $env:max_print_line = '1048576'
    New-Item -ItemType Directory -Force 'build' | Out-Null

    function Invoke-KactlLatex([string]$Source, [string]$LogName) {
        Write-Host "Compiling $Source ..."
        $consoleLog = Join-Path 'build' $LogName
        $errorLog = "$consoleLog.stderr"
        $arguments = @('-shell-escape', '-interaction=nonstopmode', '-halt-on-error', '-file-line-error', '-output-directory=build', $Source)
        $process = Start-Process -FilePath $pdfLatex -ArgumentList $arguments -WorkingDirectory $projectRoot -WindowStyle Hidden -Wait -PassThru -RedirectStandardOutput $consoleLog -RedirectStandardError $errorLog
        if ((Get-Item -LiteralPath $errorLog).Length -gt 0) {
            Get-Content -LiteralPath $errorLog | Add-Content -LiteralPath $consoleLog -Encoding UTF8
        }
        if ($process.ExitCode -ne 0) {
            Get-Content -LiteralPath $consoleLog -Tail 50 | Write-Host
            throw "LaTeX failed. See $projectRoot\$consoleLog"
        }
        if (Select-String -LiteralPath $consoleLog -Pattern 'Traceback \(most recent call last\)|Error in preprocessor|runsystem\(.*failed' -Quiet) {
            throw "A build subprocess failed. See $projectRoot\$consoleLog"
        }
    }

    if ((Test-Path -LiteralPath 'kactl.pdf') -and -not (Test-Path -LiteralPath 'build\kactl-before-windows-setup.pdf')) {
        Copy-Item -LiteralPath 'kactl.pdf' -Destination 'build\kactl-before-windows-setup.pdf'
    }
    if (-not $Fast) {
        Invoke-KactlLatex 'content/test-session/test-session.tex' 'test-session-console.log'
        Copy-Item -LiteralPath 'build\test-session.pdf' -Destination 'test-session.pdf' -Force
    }
    Invoke-KactlLatex 'content/kactl.tex' 'kactl-pass1-console.log'
    if (-not $Fast) { Invoke-KactlLatex 'content/kactl.tex' 'kactl-pass2-console.log' }
    Copy-Item -LiteralPath 'build\kactl.pdf' -Destination 'kactl.pdf' -Force
    Write-Host "Build succeeded: $projectRoot\kactl.pdf" -ForegroundColor Green
}
finally {
    Pop-Location
    foreach ($name in $previousEnvironment.Keys) {
        [Environment]::SetEnvironmentVariable($name, $previousEnvironment[$name], 'Process')
    }
}
