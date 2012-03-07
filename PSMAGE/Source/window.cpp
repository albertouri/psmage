#include <QtGui>

#include "renderArea.h"
#include "window.h"

Window::Window()
{
	// Widgets
	renderArea = new RenderArea;

	regionsSpinBox = new QSpinBox;
	regionsSpinBox->setRange(10, renderArea->getMaxRegions());

	regionsLabel = new QLabel(tr("# Regions:"));
	regionsLabel->setBuddy(regionsSpinBox);

	// Connections
	connect(regionsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(regionsChanged()));

	// Layout
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(renderArea, 0, 2, 1, 4);
	mainLayout->addWidget(regionsLabel, 0, 0, Qt::AlignRight);
	mainLayout->addWidget(regionsSpinBox, 0, 1);
	setLayout(mainLayout);

	setWindowTitle(tr("Basic Voronoi"));
}

void Window::regionsChanged()
{
	renderArea->setNumRegions(regionsSpinBox->value());
}