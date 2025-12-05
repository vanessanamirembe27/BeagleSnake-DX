#include "tonebuzzer.h"
#include <QThread>
#include <QFile>

ToneBuzzer::ToneBuzzer(QString pmwPath, QObject *parent)
    : QObject(parent), m_pmwPath(pmwPath)
{
   //Disable PMW at startup

   writeFile(m_pmwPath + "/enable", "0");
}
//write period, duty_cycle, enable
void ToneBuzzer::writeFile(QString file, QString value)
{
  QFile f(file);
  if (f.open(QIODevice::WriteOnly)) {
     f.write(value.toUtf8());
     f.close();
  }
}
//Generating a musical tone using PWM
void ToneBuzzer::playTone(int frequency, int durationMs)
{
  int periodNs = 1e9 /frequency;
  int dutyNs   = periodNs / 2;

  writeFile(m_pwmPath + "/period", QString::number(periodNs));
  writeFile(m_pwmPath + "/duty_cycle", QString::number(dutyNs));
  writeFile(m_pwmPath + "/enable", "1");

  QThread::msleep(durationMs);
  writeFile(m_pwmPath + "/enable", "0");
}
//Plays Mario Coin sound
void ToneBuzzer::playCoin()
{
  //Mario coin sound: E6 to G6
  playTone(1318,70); //E6
  playTone(1567, 70); //G6
}
//classic fail sound found in many similar games
void ToneBuzzer::playCrash()
{
  //Descending tone sequence
  playTone(988, 120); //B5
  playTone(784, 120); //G5
  playTone(659, 180); //E5
}
//short Mario start level sound
void ToneBuzzer::playMarioStart()
{
    playTone(1318, 120); //E6
    playTone(1567, 120); //G6
    playTone(2093, 150); //C7
    playTone(1567, 120); //G6
    playTone(1318, 150); //E6
}
