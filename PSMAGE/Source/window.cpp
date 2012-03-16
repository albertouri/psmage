#include <QtGui>

#include "renderArea.h"
#include "window.h"

Window::Window()
{
	// Widgets
	renderArea = new RenderArea;

	mapSizeBox = new QSpinBox;
	mapSizeBox->setRange(50, 500);
	mapSizeBox->setValue(renderArea->getMapSize());
	mapSizeLabel = new QLabel(tr("Map size:"));
	mapSizeLabel->setBuddy(mapSizeBox);

	regionsSpinBox = new QSpinBox;
	regionsSpinBox->setRange(renderArea->minRegions, renderArea->maxRegions);
	regionsSpinBox->setValue(renderArea->getNumRegions());
	regionsLabel = new QLabel(tr("# Regions:"));
	regionsLabel->setBuddy(regionsSpinBox);

	toTxtButton = new QPushButton(tr("Generate TXT Map"));
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
	mainLayout->addWidget(mapSizeLabel, 0, 0, Qt::AlignRight);
	mainLayout->addWidget(mapSizeBox, 0, 1);
	mainLayout->addWidget(regionsLabel, 1, 0, Qt::AlignRight);
	mainLayout->addWidget(regionsSpinBox, 1, 1);
	mainLayout->addWidget(generateRegionsButton, 2, 0, 1, 2);
	mainLayout->addWidget(genElevationsButton, 3, 0, 1, 2);
	mainLayout->addWidget(mirroringButton, 4, 0, 1, 2);
	mainLayout->addWidget(toTxtButton, 5, 0, 1, 2);
	mainLayout->setRowStretch(6, 50);
	setLayout(mainLayout);

	setWindowTitle(tr("Procedural Starcraft MAp GEnerator"));
}

void Window::generateRegions()
{
	renderArea->generateRegions(mapSizeBox->value(), regionsSpinBox->value());
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
	renderArea->generateTXT();
}