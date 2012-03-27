#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class RenderArea;
class QLabel;
class QSpinBox;
class QPushButton;
class QLineEdit;
class QComboBox;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window();

private slots:
	void generateRegions();
	void generateElevations();
	void mirroring();
	void generateTXT();

private:
	RenderArea *renderArea;
	QLabel *mapSizeLabel;
	QComboBox *mapSizeBox;
	QLabel *regionsLabel;
	QSpinBox *regionsSpinBox;
	QPushButton *toTxtButton;
	QPushButton *generateRegionsButton;
	QPushButton *genElevationsButton;
	QPushButton *mirroringButton;
};

#endif // WINDOW_H
