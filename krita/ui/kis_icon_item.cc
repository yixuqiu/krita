/*
 *  Copyright (c) 1999 Matthias Elter <elter@kde.org>
 *  Copyright (c) 2003 Patrick Julien  <freak@codepimps.org
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.g
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include "kis_resource.h"
#include "kis_icon_item.h"

#define THUMB_SIZE 30

KisIconItem::KisIconItem(KisResource *r)
{
	m_r = r;
	validPixmap = false;
	validThumb = false;
	m_thumb = 0;
	m_pixmap = 0;

	if (m_r && m_r -> valid()) {
		QImage img = m_r -> img();

		if (img.isNull()) {
			m_r -> setValid(false);
			m_r = 0;
			return;
		}

		if (img.width() > THUMB_SIZE || img.height() > THUMB_SIZE) {
			QImage thumb = img;
			Q_INT32 xsize = THUMB_SIZE;
			Q_INT32 ysize = THUMB_SIZE;
			Q_INT32 picW  = thumb.width();
			Q_INT32 picH  = thumb.height();

			if (picW > picH) {
				float yFactor = (float)((float)(float)picH / (float)picW);

				ysize = (Q_INT32)(yFactor * (float)THUMB_SIZE);
			
				if (ysize > THUMB_SIZE) 
					ysize = THUMB_SIZE;
			} else if (picW < picH) {
				float xFactor = (float)((float)picW / (float)picH);

				xsize = (Q_INT32)(xFactor * (float)THUMB_SIZE);

				if (xsize > THUMB_SIZE) 
					xsize = THUMB_SIZE;
			}

			thumb = thumb.smoothScale(xsize, ysize);

			if (!thumb.isNull()) {
				m_thumb = new QPixmap(thumb);
				validThumb = !m_thumb -> isNull();
			}
		}

		img = img.convertDepth(32);
		m_pixmap = new QPixmap(img);
		validPixmap = true;
		m_spacing = 7;
	}
}

KisIconItem::~KisIconItem()
{
	delete m_thumb;
	delete m_pixmap;
}

QPixmap& KisIconItem::pixmap() const
{
	return *m_pixmap;
}

QPixmap& KisIconItem::thumbPixmap() const
{
	return *m_thumb;
}

KisResource *KisIconItem::resource() const
{
	return m_r;
}

