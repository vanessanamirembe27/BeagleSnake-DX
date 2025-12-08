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
    void processNextNote(); 
    void stopCurrentNote(); 

private:
    void writeFile(const QString &filePath, const QByteArray &value);
    void setEnabled(bool enable);
    void playTone(int frequency, int durationMs); // We'll keep this to add notes to the queue
    
    QString m_pwmChannelPath; // Renamed for clarity
    QString m_pwmChipPath;   

    QQueue<Note> m_noteQueue; 
    QTimer *m_playbackTimer;  
    bool m_isPlaying = false; 
};
#endif 