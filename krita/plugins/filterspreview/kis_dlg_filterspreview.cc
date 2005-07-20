/*
 * This file is part of Krita
 *
 * Copyright (c) 2004 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include "kis_dlg_filterspreview.h"

#include <qlayout.h>
#include <qlabel.h>

#include "kis_filters_listview.h"
#include "kis_filter.h"
#include "kis_view.h"
#include "kis_previewwidget.h"
class KisPreviewView;


namespace Krita {
namespace Plugins {
namespace FiltersPreview {


KisDlgFiltersPreview::KisDlgFiltersPreview(KisView* view, QWidget* parent,const char *name)
	: KDialogBase(parent,name, true,"Preview filters action", Ok | Cancel), m_view(view),m_currentConfigWidget(0), m_currentFilter(0)
{
	QFrame* frame = makeMainWidget();
	m_hlayout = new QHBoxLayout(frame);

	
	m_kflw = new KisFiltersListView(m_view, frame  );
	m_hlayout->addWidget(m_kflw);
	connect(m_kflw, SIGNAL(selectionChanged(QIconViewItem*)), this, SLOT(selectionHasChanged(QIconViewItem* )));

	m_previewWidget = new KisPreviewWidget(frame);
	m_hlayout->addWidget(m_previewWidget);
	m_previewWidget->slotSetLayer( m_view->currentImg()->activeLayer() );
	connect(m_previewWidget, SIGNAL(updated()), this, SLOT(refreshPreview()));
	
	resize( QSize(600, 480).expandedTo(minimumSizeHint()) );

}


KisDlgFiltersPreview::~KisDlgFiltersPreview()
{
}


void KisDlgFiltersPreview::selectionHasChanged ( QIconViewItem * item )
{
	KisFiltersIconViewItem* kisitem = (KisFiltersIconViewItem*) item;
	m_currentFilter = kisitem->filter();
	if(m_currentConfigWidget != 0)
	{
		m_hlayout->remove(m_currentConfigWidget);
		delete m_currentConfigWidget;
		m_currentConfigWidget = 0;
	}
	KisImageSP img = m_view->currentImg();
	KisLayerSP activeLayer = img->activeLayer();
	m_currentConfigWidget = m_currentFilter->createConfigurationWidget(mainWidget(),(KisPaintDeviceSP)activeLayer);
	if(m_currentConfigWidget != 0)
	{
		m_hlayout->insertWidget(1, m_currentConfigWidget);
		m_currentConfigWidget->show();
		connect(m_currentConfigWidget, SIGNAL(sigPleaseUpdatePreview()), this, SLOT(refreshPreview()));
	}
	refreshPreview();
}

void KisDlgFiltersPreview::refreshPreview( )
{
	if(m_currentFilter == 0)
		return;
	m_previewWidget->slotRenewLayer();
	
	KisLayerSP layer = m_previewWidget->getLayer();

	KisFilterConfiguration* config = m_currentFilter->configuration(m_currentConfigWidget, layer.data());
	
	QRect rect = layer -> extent();
	m_currentFilter->process((KisPaintDeviceSP) layer, (KisPaintDeviceSP) layer, config, rect);
	m_previewWidget->slotUpdate();
}

};
};
};

#include "kis_dlg_filterspreview.moc"
