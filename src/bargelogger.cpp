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
  cout << "barge resource requested: " + data["url"] + "\n";
}
void BargeLogger::_resourceReceived(const QVariant& data) {
  cout << "barge resource received: " + data["url"] + "\n";
}
void BargeLogger::_resourceError(const QVariant& data) {
  cout << "barge resource error: " + data["url"] + "\n";
}
void BargeLogger::_resourceTimeout(const QVariant& data) {
  cout << "barge resource timeout: " + data["url"] + "\n";
}