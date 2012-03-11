#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class RenderArea;
class QLabel;
class QSpinBox;
class QPushButton;
class QLineEdit;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

private slots:
	void regionsChanged();
	void generateTXT();

private:
	RenderArea *renderArea;
	QLabel *mapSizeLabel;
	QSpinBox *mapSizeBox;
	QLabel *regionsLabel;
	QSpinBox *regionsSpinBox;
	QPushButton *toTxtButton;
	QPushButton *generateRegionsButton;
};

#endif // WINDOW_H
