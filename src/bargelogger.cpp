#include "bargelogger.h"
#include "networkaccessmanager.h"
#include <syslog.h>

#define UNUSED(x) (void)(x)


using namespace std;

BargeLogger::BargeLogger (NetworkAccessManager *networkAccessManager) {
  m_networkAccessManager = networkAccessManager;
  openlog("barge", 0, LOG_USER);
  connect(m_networkAccessManager, SIGNAL(resourceRequested(QVariant, QObject *)), this, SLOT(_resourceRequested(QVariant, QObject *)));
  connect(m_networkAccessManager, SIGNAL(resourceReceived(QVariant)), this, SLOT(_resourceReceived(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceError(QVariant)), this, SLOT(_resourceError(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceTimeout(QVariant)), this, SLOT(_resourceTimeout(QVariant)));
};

BargeLogger::~BargeLogger() {
  closelog();
}

void BargeLogger::_resourceRequested(const QVariant& data, QObject *) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();
  
  syslog(LOG_INFO, qPrintable("barge resource requested:" + url));
}
void BargeLogger::_resourceReceived(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();

  QTextStream cout(stdout);
  cout << "barge resource received:" << url << "\n";
}
void BargeLogger::_resourceError(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();

  QTextStream cout(stdout);
  cout << "barge resource error:" << url << "\n";
}
void BargeLogger::_resourceTimeout(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();

  QTextStream cout(stdout);
  cout << "barge resource timeout:" << url << "\n";
}