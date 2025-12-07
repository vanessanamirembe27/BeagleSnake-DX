#include "tonebuzzer.h"
#include <QFile>
#include <QDebug> // Good for debugging
#include <QDir>      // <-- ADD THIS
#include <QThread> // Add this for the delay

ToneBuzzer::ToneBuzzer(const QString &pwmChipPath, QObject *parent)
    : QObject(parent), m_pwmChipPath(pwmChipPath)
{
    writeFile("/sys/devices/platform/ocp/ocp:P9_14_pinmux/state", "pwm");

    m_pwmChannelPath = m_pwmChipPath + "/pwm-4:0";

    // --- THIS IS THE NEW EXPORT LOGIC ---
    QDir pwmChannelDir(m_pwmChannelPath);
    // Check if the pwm0 directory does NOT exist
    if (!pwmChannelDir.exists()) {
        qDebug() << "ToneBuzzer: Exporting PWM channel 0...";
        // Write "0" to the export file to create the pwm4 channel directory
        writeFile(m_pwmChipPath + "/export", "0");
        QThread::msleep(100);
    }
    // --- END OF NEW LOGIC ---
    // Set up the timer
    m_playbackTimer = new QTimer(this);
    // Connect the timer's timeout signal to our slot that stops the current note
    connect(m_playbackTimer, &QTimer::timeout, this, &ToneBuzzer::stopCurrentNote);

    // Ensure buzzer is off at start
    setEnabled(false);
}

ToneBuzzer::~ToneBuzzer()
{
    setEnabled(false);
}

void ToneBuzzer::playCoin()
{
    // Add the notes for the "coin" sound to the queue
    playTone(1047, 100); // C6
    playTone(1397, 150); // F6
}

void ToneBuzzer::playCrash()
{
    // Add the notes for the "crash" sound to the queue
    playTone(130, 120); // C3
    playTone(123, 150); // B2
    playTone(116, 150); // A#2
}

void ToneBuzzer::playStartSound()
{
    // Mario Kart-style countdown sound
    playTone(880, 100);  // A5 beep
    playTone(0, 50);     // Pause
    playTone(880, 100);  // A5 beep
    playTone(0, 50);     // Pause
    playTone(1047, 200); // C6 final beep
}

// This function now adds a note to the queue and starts playback if needed
void ToneBuzzer::playTone(int frequency, int durationMs)
{
    m_noteQueue.enqueue({frequency, durationMs});
    
    // If we aren't already playing a sequence, start a new one.
    if (!m_isPlaying) {
        processNextNote();
    }
}

// This is the core of the new non-blocking logic
void ToneBuzzer::processNextNote()
{
    // If the queue is empty, we're done.
    if (m_noteQueue.isEmpty()) {
        m_isPlaying = false;
        return;
    }

    m_isPlaying = true;
    Note currentNote = m_noteQueue.dequeue();

    if (currentNote.frequency > 0) {
        // Calculate period and duty cycle
        long period = 1e9 / currentNote.frequency;
        long duty_cycle = period / 2; // 50% duty cycle

        // Use the channel path for writing
        writeFile(m_pwmChannelPath + "/period", QByteArray::number(static_cast<qlonglong>(period)));
        writeFile(m_pwmChannelPath + "/duty_cycle", QByteArray::number(static_cast<qlonglong>(duty_cycle)));
        setEnabled(true);

        // Start the timer to stop this note after its duration
        m_playbackTimer->start(currentNote.durationMs);
    } else {
        // If frequency is 0, it's a rest. Just wait for the duration.
        setEnabled(false);
        m_playbackTimer->start(currentNote.durationMs);
    }
}

// This slot is called when the timer finishes for the current note
void ToneBuzzer::stopCurrentNote()
{
    m_playbackTimer->stop();
    setEnabled(false);
    
    // Immediately process the next note in the queue
    processNextNote();
}

void ToneBuzzer::setEnabled(bool enable)
{
    writeFile(m_pwmChannelPath + "/enable", enable ? "1" : "0");
}

void ToneBuzzer::writeFile(const QString &filePath, const QByteArray &value)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(value);
        file.close();
    } else {
        qWarning() << "ToneBuzzer: Could not write to" << filePath;
    }
}