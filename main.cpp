#include <logger.h>
#include <factory.h>

#include <QString>
#include <QByteArray>
#include <QMap>
#include <QLibrary>
#include <QDebug>

int main()
{
    typedef ad::Factory<QByteArray> factory_t;
    typedef ad::Logger<QString, QMap<QString, QString>> logger_t;
    typedef factory_t* (*LoggerFactoryGetter)();
    LoggerFactoryGetter getFactory = (LoggerFactoryGetter)QLibrary::resolve("/home/arsdever/projects/testing/logger","getFactory");
    if(getFactory == nullptr)
        return -1;

    factory_t *factory = getFactory();
    if(factory == nullptr)
        return -2;

    factory->configureWithFile("logger.conf");
    logger_t *logger = (logger_t*)factory->getInstance();
    logger->log(ad::LogLevel::Info, "Hello world");
    return 0;
}