#ifndef TONEBUZZER_H
#define TONEBUZZER_H
#include <QObject>
#include <QString>

class ToneBuzzer : public QObject
{
    Q_OBJECT
public: 
    explicit ToneBuzzer(QString pwmPath, QObject *parent = nullptr);

    void playTone(int frequency, int durationMs);
    void playCoin();  //Mario coin sound
    void playCrash(); //collision sound

private:
    QString m_pwmPath;
    void writeFile(QString file, QString value);
};
#endif 
