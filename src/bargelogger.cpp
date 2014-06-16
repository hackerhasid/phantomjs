#include "bargelogger.h"
#include "networkaccessmanager.h"
#define UNUSED(x) (void)(x)

BargeLogger::BargeLogger (NetworkAccessManager *networkAccessManager) {
  m_networkAccessManager = networkAccessManager;
  connect(m_networkAccessManager, SIGNAL(resourceRequested(QVariant, QObject *)), this, SLOT(_resourceRequested(QVariant, QObject *)));
  connect(m_networkAccessManager, SIGNAL(resourceReceived(QVariant)), this, SLOT(_resourceReceived(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceError(QVariant)), this, SLOT(_resourceError(QVariant)));
  connect(m_networkAccessManager, SIGNAL(resourceTimeout(QVariant)), this, SLOT(_resourceTimeout(QVariant)));
};

void BargeLogger::_resourceRequested(const QVariant& data, QObject *) {
  UNUSED(data);
  cout << "barge resource requested";
}
void BargeLogger::_resourceReceived(const QVariant& data) {
  UNUSED(data);
  cout << "barge resource received";
}
void BargeLogger::_resourceError(const QVariant& data) {
  UNUSED(data);
  cout << "barge resource error";
}
void BargeLogger::_resourceTimeout(const QVariant& data) {
  UNUSED(data);
  cout << "barge resource timeout";
}