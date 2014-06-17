class NetworkAccessManager;

#include <QVariant>

class BargeLogger : public QObject {
  Q_OBJECT
  
public:
    BargeLogger(NetworkAccessManager *m_networkAccessManager);
    virtual ~BargeLogger;

private slots:
  void _resourceRequested(const QVariant& data, QObject *);
  void _resourceReceived(const QVariant& data);
  void _resourceError(const QVariant& data);
  void _resourceTimeout(const QVariant& data);

private:
  NetworkAccessManager *m_networkAccessManager;
};