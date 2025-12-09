#ifndef TONEBUZZER_H
#define TONEBUZZER_H
#include <QObject>
#include <QString>
#include <QQueue>
#include <QTimer> 

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
    void playTone(int frequency, int durationMs);
    
    QString m_pwmChannelPath;
    QString m_pwmChipPath;   

    QQueue<Note> m_noteQueue; 
    QTimer *m_playbackTimer;  
    bool m_isPlaying = false; 
};
#endif 