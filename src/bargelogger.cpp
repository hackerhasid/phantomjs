#include "bargelogger.h"
#include "networkaccessmanager.h"
#include<iostream>

#define UNUSED(x) (void)(x)


using namespace std;

BargeLogger::BargeLogger (NetworkAccessManager *networkAccessManager) {
  m_networkAccessManager = networkAccessManager;
  connect(m_networkAccessManager, SIGNAL(resourceRequested(QVariant, QObject *)), this, SLOT(_resourceRequested(QVariant, QObject *)));
  connect(m_networkAccessManager, SIGNAL(resourceReceived(QVariant)), this, SLOT(_resourceReceived(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceError(QVariant)), this, SLOT(_resourceError(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceTimeout(QVariant)), this, SLOT(_resourceTimeout(QVariant)));
};

void BargeLogger::_resourceRequested(const QVariant& data, QObject *request) {
  if (false) { // TODO: add cdn urls or something?
    request.abort();
  }

  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();
  cout << "barge resource requested: ";
  cout << url;
  cout << "\n";
}
void BargeLogger::_resourceReceived(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();
  cout << "barge resource received: ";
  cout << url;
  cout << "\n";
}
void BargeLogger::_resourceError(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();
  cout << "barge resource error: ";
  cout << url;
  cout << "\n";
}
void BargeLogger::_resourceTimeout(const QVariant& data) {
  QMap<QString, QVariant> dataMap = data.toMap();
  QString url = dataMap.value("url").toString();
  cout << "barge resource timeout: ";
  cout << data["url"];
  cout << "\n";
}