#include "bargelogger.h"
#include "networkaccessmanager.h"
#include <syslog.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

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
  QJsonObject obj;
  obj["task"] = QString("resourceRequested");
  obj["url"] = dataMap.value("url").toString();
  QJsonDocument doc = QJsonDocument(obj).toJson(QJsonDocument::Compact);
  syslog(LOG_INFO, doc.constData());
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