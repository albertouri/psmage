#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class RenderArea;
class QLabel;
class QSpinBox;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

private slots:
	void regionsChanged();

private:
	RenderArea *renderArea;
	QLabel *mapWLabel;
	QSpinBox *mapWidthSpinBox;
	QLabel *mapHLabel;
	QSpinBox *mapHeightSpinBox;
	QLabel *regionsLabel;
	QSpinBox *regionsSpinBox;
};

#endif // WINDOW_H
