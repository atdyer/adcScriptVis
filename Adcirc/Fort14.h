#ifndef FORT14_H
#define FORT14_H

#include <QObject>
#include <QDebug>

class Fort14 : public QObject
{
		Q_OBJECT
	public:
		explicit Fort14(QObject *parent = 0);

	signals:

	public slots:

		int	numNodes();
		int	numElements();

};

#endif // FORT14_H
