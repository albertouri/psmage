#include <QtGui>

#include "renderArea.h"
#include "window.h"

Window::Window()
{
	// Widgets
	renderArea = new RenderArea;

	mapSizeBox = new QComboBox;
	// remember: 
	//	walk tiles are (8x8) pixels
	//	build tiles are (32x32) pixels
	mapSizeBox->addItem("64x64", QVariant(64));
	mapSizeBox->addItem("96x96", QVariant(96));
	mapSizeBox->addItem("128x128", QVariant(128));
	mapSizeBox->addItem("196x196", QVariant(196));
	mapSizeBox->addItem("256x256", QVariant(256));
	mapSizeBox->setCurrentIndex(2);
	mapSizeLabel = new QLabel(tr("Map size:"));
	mapSizeLabel->setBuddy(mapSizeBox);

	regionsSpinBox = new QSpinBox;
	regionsSpinBox->setRange(renderArea->minRegions, renderArea->maxRegions);
	regionsSpinBox->setValue(renderArea->getNumRegions());
	regionsLabel = new QLabel(tr("# Regions:"));
	regionsLabel->setBuddy(regionsSpinBox);

	toTxtButton = new QPushButton(tr("Generate CHK Map"));
	generateRegionsButton = new QPushButton(tr("Generate Regions"));
	genElevationsButton = new QPushButton(tr("Generate Elevations"));
	mirroringButton = new QPushButton(tr("Mirroring Map"));

	// Connections
	//connect(regionsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(regionsChanged()));
	connect(toTxtButton, SIGNAL(clicked()), this, SLOT(generateTXT()));
	connect(generateRegionsButton, SIGNAL(clicked()), this, SLOT(generateRegions()));
	connect(genElevationsButton, SIGNAL(clicked()), this, SLOT(generateElevations()));
	connect(mirroringButton, SIGNAL(clicked()), this, SLOT(mirroring()));

	// Layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 2, 7, 1);
	mainLayout->addWidget(regionsLabel, 0, 0, Qt::AlignRight);
	mainLayout->addWidget(regionsSpinBox, 0, 1);
	mainLayout->addWidget(generateRegionsButton, 1, 0, 1, 2);
	mainLayout->addWidget(genElevationsButton, 2, 0, 1, 2);
	mainLayout->addWidget(mirroringButton, 3, 0, 1, 2);
	mainLayout->addWidget(mapSizeLabel, 4, 0, Qt::AlignRight);
	mainLayout->addWidget(mapSizeBox, 4, 1);
	mainLayout->addWidget(toTxtButton, 5, 0, 1, 2);
	mainLayout->setRowStretch(6, 50);
	setLayout(mainLayout);

	setWindowTitle(tr("Procedural Starcraft MAp GEnerator"));
}

void Window::generateRegions()
{
	renderArea->generateRegions(regionsSpinBox->value());
}

void Window::generateElevations()
{
	renderArea->generateElevations();
}

void Window::mirroring()
{
	renderArea->mirroringMap();
}

void Window::generateTXT()
{
	int mapSize = mapSizeBox->itemData(mapSizeBox->currentIndex()).toInt();
	renderArea->generateTXT(mapSize);
}