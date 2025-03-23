#pragma once
#include<QAbstractTableModel>
#include<Domeniu.h>
#include<vector>
#include<string>
using std::string;
using std::vector;
class TableModel : public QAbstractTableModel {
private:
	vector<Game> games;
public:
	TableModel(vector<Game>& games) :games{ games } {};
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return games.size();
	}
	int columnCount(const QModelIndex& perent = QModelIndex()) const override{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole()) const override {
		if (role == Qt::DisplayRole) {
			Game g  = games[index.row()];
			if (index.column() == 0)
				return QString::number(g.getId());
			else if (index.column() == 1)
				return QString::number(g.getDim());
			else if (index.column() == 2)
				return QString::fromStdString(g.getBoard());
			else if (index.column() == 3) {
				if (g.getGamer() == 'X')
					return QChar('X');
				else
					return QChar('O');

			}
			else if (index.column() == 4)
				return QString::fromStdString(g.getStatus());
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
		{
			if (section == 0)
				return "ID";
			if (section == 1)
				return "SIZE";
			if (section == 2)
				return "BOARD";
			if (section == 3)
				return "GAMER";
			if (section == 4)
				return "STATUS";
		}
		return QVariant();
	}

	void setGames(const vector<Game>& games) {
		this->games = games;
		auto topLeft = createIndex(0, 0);
		auto bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}


};