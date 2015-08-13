/*
    This file is part of etherwall.
    etherwall is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    etherwall is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with etherwall. If not, see <http://www.gnu.org/licenses/>.
*/
/** @file transactionmodel.h
 * @author Ales Katona <almindor@gmail.com>
 * @date 2015
 *
 * Transaction model header
 */


#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H


#include <QAbstractListModel>
#include "types.h"
#include "etheripc.h"

namespace Etherwall {

    class TransactionModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(quint64 blockNumber READ getBlockNumber NOTIFY blockNumberChanged FINAL)
    public:
        TransactionModel(const EtherIPC& ipc);
        quint64 getBlockNumber() const;
        QHash<int, QByteArray> roleNames() const;
        int rowCount(const QModelIndex & parent = QModelIndex()) const;
        QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    public slots:
        void connectToServerDone();
        void getTransactionsDone(const TransactionList& list);
        void getBlockNumberDone(quint64 num);
    signals:
        void connectToServerIPC(const QString& path);
        void getTransactionsIPC();
        void getBlockNumberIPC();

        void blockNumberChanged(quint64 num);
    private:
        TransactionList fTransactionList;
        quint64 fBlockNumber;

        void refresh();
    };

}


#endif // TRANSACTIONMODEL_H
