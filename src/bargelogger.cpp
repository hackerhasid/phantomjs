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
  QString json = QString("{\"task\":\"resourceRequested\",\"url\":\"%1\"}").arg(dataMap.value("url").toString());
  syslog(LOG_INFO, qPrintable(json));
}
void BargeLogger::_resourceReceived(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString json = QString("{\"task\":\"resourceReceived\",\"url\":\"%1\"}").arg(dataMap.value("url").toString());
  syslog(LOG_INFO, qPrintable(json));
}
void BargeLogger::_resourceError(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  // QString json = QString("{\"task\":\"resourceError\",\"url\":\"%1\",\"errorCode\":\"%2\"}")
  //   .arg(dataMap.value("url").toString())
  //   .arg(dataMap.value("errorCode").toString());
  // syslog(LOG_ERR, qPrintable(json));
}
void BargeLogger::_resourceTimeout(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString json = QString("{\"task\":\"resourceTimeout\",\"url\":\"%1\"}").arg(dataMap.value("url").toString());
  syslog(LOG_ERR, qPrintable(json));
}