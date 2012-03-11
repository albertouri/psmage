#include <QtGui>

#include "renderArea.h"
#include "window.h"

Window::Window()
{
	// Widgets
	renderArea = new RenderArea;

	mapSizeBox = new QSpinBox;
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

	// Connections
	//connect(regionsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(regionsChanged()));
	connect(toTxtButton, SIGNAL(clicked()), this, SLOT(generateTXT()));
	connect(generateRegionsButton, SIGNAL(clicked()), this, SLOT(regionsChanged()));

	// Layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 2, 5, 1);
	mainLayout->addWidget(mapSizeLabel, 0, 0, Qt::AlignRight);
	mainLayout->addWidget(mapSizeBox, 0, 1);
	mainLayout->addWidget(regionsLabel, 1, 0, Qt::AlignRight);
	mainLayout->addWidget(regionsSpinBox, 1, 1);
	mainLayout->addWidget(generateRegionsButton, 2, 0, 1, 2);
	mainLayout->addWidget(toTxtButton, 3, 0, 1, 2);
	mainLayout->setRowStretch(4, 50);
	setLayout(mainLayout);

	setWindowTitle(tr("Basic Voronoi"));
}

void Window::regionsChanged()
{
	renderArea->setMapSize(mapSizeBox->value());
	renderArea->setNumRegions(regionsSpinBox->value());
}

void Window::generateTXT()
{
	renderArea->generateTXT();
}