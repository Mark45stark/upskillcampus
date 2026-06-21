void setup()
{
    getWiFiCredentials();
    getServerCredentials();

    connectToWiFi();

    if (!wifiConnected())
    {
        startAccessPointMode();
        receiveWiFiCredentials();
        connectToWiFi();
    }

    initializeRelay();
    initializeSwitch();

    startLoop();
}

void loop()
{
    if (wifiConnected())
    {
        checkServerStatus();
        checkMobileAppCommands();
    }

    checkManualSwitchStatus();

    if (mobileCommandReceived())
    {
        updateRelayStatus();
    }

    if (manualSwitchPressed())
    {
        toggleRelay();
        updateCloudStatus();
    }

    sendDeviceStatusToServer();

    delay(100);
}
