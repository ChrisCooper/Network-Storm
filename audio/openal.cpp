#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

typedef ALuint auint;
typedef ALfloat afloat;
typedef ALboolean abool;

auint buffer;
auint source;

// Source position and velocity x,y,z
afloat sourcepos[] = {0., 0., 0.};
afloat sourcevel[] = {0., 0., 0.};

// listen position and velocity x,y,z
afloat listenpos[] = {0., 0., 0.};
afloat listenvel[] = {0., 0., 0.};
// listen orientation: First 3 "at", last 3 "up"
// TODO: What does this mean?
afloat listenori[] = {0., 0., -1, 0., 1., 0.};

abool load(ALbyte* filename) {
    ALenum format;
    ALsizei size;
    ALvoid* data;
    ALsizei freq;
    abool loop;

    // Create some buffers
    alGenBuffers(1, &buffer);
    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;

    // Load the data into the buffer
    alutLoadWAVFile(filename, &format, &data, &size, &freq, &loop);
    alBufferData(buffer, format, data, size, freq);
    alutUnloadWAV(format, data, size, freq);

    alGenSources(1, &source);
    if (alGetError() != AL_NO_ERROR)
        return AL_FALSE;

    // Set source's data source (buffer)
    alSourcei(source, AL_BUFFER, buffer);
    // Set source properties
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcefv(source, AL_POSITION, sourcepos);
    alSourcefv(source, AL_VELOCITY, sourcevel);
    alSourcei(source, AL_LOOPING, loop);

    
    if (alGetError() == AL_NO_ERROR)
        return AL_TRUE;

    return AL_FALSE;
}

int main(int argc, char* argv[]) {
    alutInit(&argc, argv);
    alGetError();

    char fn[] = "tmp.wav";
    if (load((ALbyte*) fn) == AL_FALSE) return -1;

    // Set listen properties
    // listen is part of AL context, so doesn't have its own object
    alListenerfv(AL_POSITION, listenpos);
    alListenerfv(AL_VELOCITY, listenvel);
    alListenerfv(AL_ORIENTATION, listenori);

    char c = ' ';
    while (c != 'q') {
        std::cin >> c;
        switch(c) {
            case 'p': alSourcePlay(source);
                      break;
            case 's': alSourceStop(source);
                      break;
            case 'h': alSourcePause(source);
                      break;
        }
    }

    alDeleteBuffers(1, &buffer);
    alDeleteSources(1, &source);
    alutExit();
    return 0;
}
