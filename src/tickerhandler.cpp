/*
 * Copyright (C) 2014 Alexander Schoedon <schoedon@uni-potsdam.de>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDateTime>
#include <QStandardPaths>
#include "tickerhandler.h"

namespace {
    static const int     VERSION_MAJOR   = 1;
    static const int     VERSION_MINOR   = 7;
    static const QString VERSION_STRING  = "1";
    static const QString RELEASE_DATE    = "03/December/2014";
}

TickerHandler::TickerHandler(QObject *parent)
  :   QObject(parent)
  ,   m_updated(1)
  ,   m_bitfinex(this)
  ,   m_cryptsy(this)
  ,   m_poloniex(this)
  ,   m_settings(QString(QStandardPaths::ConfigLocation), QSettings::NativeFormat, this)
{
    setDefaults();

    if (!isOfflineMode())
        update();
}

TickerHandler::~TickerHandler()
{
}

void TickerHandler::setDefaults()
{
    if (m_settings.allKeys().contains("update/interval", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("update");
        setUpdateInterval(m_settings.value("interval", 5).toInt());
        m_settings.endGroup();
    }
    else
    {
        setUpdateInterval();
    }

    if (m_settings.allKeys().contains("update/offline", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("update");
        setOfflineMode(m_settings.value("offline", false).toBool());
        m_settings.endGroup();
    }
    else
    {
        setOfflineMode();
    }

    if (m_settings.allKeys().contains("coins/btc", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setBtcEnabled(m_settings.value("btc", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setBtcEnabled();
    }

    if (m_settings.allKeys().contains("coins/drk", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setDrkEnabled(m_settings.value("drk", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setDrkEnabled();
    }

    if (m_settings.allKeys().contains("coins/anc", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setAncEnabled(m_settings.value("anc", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setAncEnabled();
    }

    if (m_settings.allKeys().contains("coins/btcd", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setBtcdEnabled(m_settings.value("btcd", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setBtcdEnabled();
    }

    if (m_settings.allKeys().contains("coins/cloak", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setCloakEnabled(m_settings.value("cloak", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setCloakEnabled();
    }

    if (m_settings.allKeys().contains("coins/xmr", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setXmrEnabled(m_settings.value("xmr", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setXmrEnabled();
    }

    if (m_settings.allKeys().contains("coins/xc", Qt::CaseInsensitive))
    {
        m_settings.beginGroup("coins");
        setXcEnabled(m_settings.value("xc", true).toBool());
        m_settings.endGroup();
    }
    else
    {
        setXcEnabled();
    }
}

void TickerHandler::update(bool forced)
{
    if (!isOfflineMode() || forced)
    {
        if (m_updated <= (QDateTime().currentDateTime().toTime_t() - (m_updateInterval * 60)) || forced)
        {
            m_bitfinex.fetch();
            m_cryptsy.fetch();
            m_poloniex.fetch();
            m_updated = QDateTime().currentDateTime().toTime_t();
        }
    }
}

void TickerHandler::setUpdateInterval(int interval)
{
    if (interval < 1)
    {
        interval = 1;
    }
    else if (interval > 99)
    {
        interval = 99;
    }
    m_settings.beginGroup("update");
    m_settings.setValue("interval", interval);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("update");
    m_settings.endGroup();
    m_updateInterval = interval;
}

void TickerHandler::setOfflineMode(bool enabled)
{
    m_settings.beginGroup("update");
    m_settings.setValue("offline", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("update");
    m_settings.endGroup();
    m_offlineMode = enabled;
}

void TickerHandler::setBtcEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("btc", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_btcEnabled = enabled;
}

void TickerHandler::setDrkEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("drk", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_drkEnabled = enabled;
}

void TickerHandler::setAncEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("anc", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_ancEnabled = enabled;
}

void TickerHandler::setBtcdEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("btcd", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_btcdEnabled = enabled;
}

void TickerHandler::setCloakEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("cloak", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_cloakEnabled = enabled;
}

void TickerHandler::setXmrEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("xmr", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_xmrEnabled = enabled;
}

void TickerHandler::setXcEnabled(bool enabled)
{
    m_settings.beginGroup("coins");
    m_settings.setValue("xc", enabled);
    m_settings.endGroup();
    m_settings.sync();
    sync();
    m_settings.beginGroup("coins");
    m_settings.endGroup();
    m_xcEnabled = enabled;
}

int TickerHandler::updateInterval()
{
    return m_updateInterval;
}

bool TickerHandler::isOfflineMode()
{
    return m_offlineMode;
}

bool TickerHandler::isBtcEnabled()
{
    return m_btcEnabled;
}

bool TickerHandler::isDrkEnabled()
{
    return m_drkEnabled;
}

bool TickerHandler::isAncEnabled()
{
    return m_ancEnabled;
}

bool TickerHandler::isBtcdEnabled()
{
    return m_btcdEnabled;
}

bool TickerHandler::isCloakEnabled()
{
    return m_cloakEnabled;
}

bool TickerHandler::isXmrEnabled()
{
    return m_xmrEnabled;
}

bool TickerHandler::isXcEnabled()
{
    return m_xcEnabled;
}

QString TickerHandler::bitfinexBtcUsd()
{
    QString ticker("BTC disabled.");
    if (isBtcEnabled()) {
        if (m_bitfinex.getBtcUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_bitfinex.getBtcUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::bitfinexDrkUsd()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_bitfinex.getDrkUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_bitfinex.getDrkUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::bitfinexDrkBtc()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_bitfinex.getDrkBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_bitfinex.getDrkBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyBtcUsd()
{
    QString ticker("BTC disabled.");
    if (isBtcEnabled()) {
        if (m_cryptsy.getBtcUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_cryptsy.getBtcUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyDrkUsd()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_cryptsy.getDrkUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_cryptsy.getDrkUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyDrkBtc()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_cryptsy.getDrkBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_cryptsy.getDrkBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyDrkLtc()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_cryptsy.getDrkLtc() > 0.0f)
        {
            ticker = QString("LTC ").append(QString::number(m_cryptsy.getDrkLtc(), 'f', 3));
        }
        else
        {
            ticker = QString("LTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyAncBtc()
{
    QString ticker("ANC disabled.");
    if (isAncEnabled()) {
        if (m_cryptsy.getAncBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_cryptsy.getAncBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyAncLtc()
{
    QString ticker("ANC disabled.");
    if (isAncEnabled()) {
        if (m_cryptsy.getAncLtc() > 0.0f)
        {
            ticker = QString("LTC ").append(QString::number(m_cryptsy.getAncLtc(), 'f', 3));
        }
        else
        {
            ticker = QString("LTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyBtcdBtc()
{
    QString ticker("BTCD disabled.");
    if (isBtcdEnabled()) {
        if (m_cryptsy.getBtcdBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_cryptsy.getBtcdBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyCloakBtc()
{
    QString ticker("CLOAK disabled.");
    if (isCloakEnabled()) {
        if (m_cryptsy.getCloakBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_cryptsy.getCloakBtc(), 'f', 7));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyCloakLtc()
{
    QString ticker("CLOAK disabled.");
    if (isCloakEnabled()) {
        if (m_cryptsy.getCloakLtc() > 0.0f)
        {
            ticker = QString("LTC ").append(QString::number(m_cryptsy.getCloakLtc(), 'f', 5));
        }
        else
        {
            ticker = QString("LTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyXcBtc()
{
    QString ticker("XC disabled.");
    if (isXcEnabled()) {
        if (m_cryptsy.getXcBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_cryptsy.getXcBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::cryptsyXcLtc()
{
    QString ticker("XC disabled.");
    if (isXcEnabled()) {
        if (m_cryptsy.getXcLtc() > 0.0f)
        {
            ticker = QString("LTC ").append(QString::number(m_cryptsy.getXcLtc(), 'f', 3));
        }
        else
        {
            ticker = QString("LTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexBtcUsd()
{
    QString ticker("BTC disabled.");
    if (isBtcEnabled()) {
        if (m_poloniex.getBtcUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_poloniex.getBtcUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexXmrUsd()
{
    QString ticker("XMR disabled.");
    if (isXmrEnabled()) {
        if (m_poloniex.getXmrUsd() > 0.0f)
        {
            ticker = QString("USD ").append(QString::number(m_poloniex.getXmrUsd(), 'f', 2));
        }
        else
        {
            ticker = QString("USD ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexDrkBtc()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_poloniex.getDrkBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_poloniex.getDrkBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexDrkXmr()
{
    QString ticker("DRK disabled.");
    if (isDrkEnabled()) {
        if (m_poloniex.getDrkXmr() > 0.0f)
        {
            ticker = QString("XMR ").append(QString::number(m_poloniex.getDrkXmr(), 'f', 3));
        }
        else
        {
            ticker = QString("XMR ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexBtcdBtc()
{
    QString ticker("BTCD disabled.");
    if (isBtcdEnabled()) {
        if (m_poloniex.getBtcdBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_poloniex.getBtcdBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexBtcdXmr()
{
    QString ticker("BTCD disabled.");
    if (isBtcdEnabled()) {
        if (m_poloniex.getBtcdXmr() > 0.0f)
        {
            ticker = QString("XMR ").append(QString::number(m_poloniex.getBtcdXmr(), 'f', 3));
        }
        else
        {
            ticker = QString("XMR ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexXcBtc()
{
    QString ticker("XC disabled.");
    if (isXcEnabled()) {
        if (m_poloniex.getXcBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_poloniex.getXcBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::poloniexXmrBtc()
{
    QString ticker("XMR disabled.");
    if (isXmrEnabled()) {
        if (m_poloniex.getXmrBtc() > 0.0f)
        {
            ticker = QString("BTC ").append(QString::number(m_poloniex.getXmrBtc(), 'f', 5));
        }
        else
        {
            ticker = QString("BTC ---");
        }
        if (isOfflineMode()) {
            ticker = ticker.append(" (cached)");
        }
    }
    return ticker;
}

QString TickerHandler::version(bool shrt)
{
    if (shrt)
    {
        return QString::number(VERSION_MAJOR).append(".").append(QString::number(VERSION_MINOR));
    }
    else
    {
        return QString::number(VERSION_MAJOR).append(".").append(QString::number(VERSION_MINOR)).append("-").append(VERSION_STRING);
    }
}

QString TickerHandler::versionDate()
{
    return RELEASE_DATE;
}
