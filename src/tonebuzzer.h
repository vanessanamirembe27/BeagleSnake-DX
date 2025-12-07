#ifndef TONEBUZZER_H
#define TONEBUZZER_H
#include <QObject>
#include <QString>
#include <QQueue> // <-- Add
#include <QTimer>  // <-- Add

// A simple struct to hold a note
struct Note {
    int frequency;
    int durationMs;
};

class ToneBuzzer : public QObject
{
    Q_OBJECT
public:
    explicit ToneBuzzer(const QString &pwmChipPath, QObject *parent = nullptr);
    ~ToneBuzzer();

    void playCoin();
    void playCrash();
    void playStartSound(); 

private slots:
    void processNextNote(); // <-- Add: Slot to play the next note in the queue
    void stopCurrentNote(); // <-- Add: Slot to stop the current note after its duration

private:
    void writeFile(const QString &filePath, const QByteArray &value);
    void setEnabled(bool enable);
    void playTone(int frequency, int durationMs); // We'll keep this to add notes to the queue
    
    QString m_pwmChannelPath; // Renamed for clarity
    QString m_pwmChipPath;    // <-- ADD THIS

    QQueue<Note> m_noteQueue; // <-- Add: The queue of notes to play
    QTimer *m_playbackTimer;  // <-- Add: The timer to drive the playback
    bool m_isPlaying = false; // <-- Add: A flag to prevent overlapping notes
};
#endif 