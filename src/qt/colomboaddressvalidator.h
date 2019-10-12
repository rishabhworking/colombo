// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Colombo Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CLM_QT_CLMADDRESSVALIDATOR_H
#define CLM_QT_CLMADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class ColomboAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ColomboAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Colombo address widget validator, checks for a valid colombo address.
 */
class ColomboAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ColomboAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // CLM_QT_CLMADDRESSVALIDATOR_H
