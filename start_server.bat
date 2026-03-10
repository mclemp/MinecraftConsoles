@echo off
setlocal

set "ROOT=%~dp0"
start "" "%ROOT%x64\Debug\Minecraft.Client.exe" -server
