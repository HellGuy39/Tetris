#ifndef SETTINGSMODELS_H
#define SETTINGSMODELS_H

class MainWindowModel
{
    public:
        MainWindowModel(bool isMusicMuted = false, bool isSfxMuted = false)
        {
            _isMusicMuted = isMusicMuted;
            _isSfxMuted = isSfxMuted;
        }
        // Getters
        bool getIsMusicMuted() { return _isMusicMuted; }
        bool getIsSfxMuted() { return _isSfxMuted;}

    private:
        bool _isMusicMuted;
        bool _isSfxMuted;
};

class SoundModel
{
    public:
        SoundModel(int musicVolume = 50, int sfxVolume = 50)
        {
            _musicVolume = musicVolume;
            _sfxVolume = sfxVolume;
        }
        // Getters
        int getMusicVolume() { return _musicVolume; }
        int getSfxVolume() { return _sfxVolume; }

    private:
        int _musicVolume;
        int _sfxVolume;
};

class ControlsModel
{
    public:
        ControlsModel(int keyDown, int keyRight, int keyLeft, int keyRotate, int keyPause, int keyStart)
        {
            _keyDown = keyDown;
            _keyRight = keyRight;
            _keyLeft = keyLeft;
            _keyRotate = keyRotate;
            _keyPause = keyPause;
            _keyStart = keyStart;
        }
        // Getters
        int getKeyDown() { return _keyDown; }
        int getKeyRight() { return _keyRight; }
        int getKeyLeft() { return _keyLeft; }
        int getKeyRotate() { return _keyRotate; }
        int getKeyPause() { return _keyPause; }
        int getKeyStart() { return _keyStart; }
        // Setters
        void setKeyDown(int keyDown) { _keyDown = keyDown; }
        void setKeyRight(int keyRight) { _keyRight = keyRight; }
        void setKeyLeft(int keyLeft) { _keyLeft = keyLeft; }
        void setKeyRotate(int keyRotate) { _keyRotate = keyRotate; }
        void setKeyPause(int keyPause) { _keyPause = keyPause; }
        void setKeyStart(int keyStart) { _keyStart = keyStart; }


    private:
        int _keyDown;
        int _keyRight;
        int _keyLeft;
        int _keyRotate;
        int _keyPause;
        int _keyStart;
};


#endif // SETTINGSMODELS_H
