/*
 *  SPDX-FileCopyrightText: 2005 Adrian Page <adrian@pagenet.plus.com>
 *  SPDX-FileCopyrightText: 2008 Bart Coppens <kde@bartcoppens.be>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "KoRgbU8ColorSpaceTester.h"

#include "KoColorModelStandardIds.h"

#include <QTest>
#include <DebugPigment.h>
#include <string.h>

#include "KoColor.h"
#include "KoColorSpace.h"
#include "KoColorSpaceRegistry.h"
#include "KoCompositeOp.h"
#include "KoMixColorsOp.h"
#include <KoCompositeOpRegistry.h>
#include "sdk/tests/kistest.h"


#define NUM_CHANNELS 4

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2
#define ALPHA_CHANNEL 3
#include <KoColorProfile.h>

void KoRgbU8ColorSpaceTester::testBasics()
{
}

#define PIXEL_RED 0
#define PIXEL_GREEN 1
#define PIXEL_BLUE 2
#define PIXEL_ALPHA 3

void KoRgbU8ColorSpaceTester::testMixColors()
{
    const KoColorSpace* cs = KoColorSpaceRegistry::instance()->rgb8();
    KoMixColorsOp * mixOp = cs->mixColorsOp();

    // Test mixColors.
    quint8 pixel1[4];
    quint8 pixel2[4];
    quint8 outputPixel[4];

    pixel1[PIXEL_RED] = 255;
    pixel1[PIXEL_GREEN] = 255;
    pixel1[PIXEL_BLUE] = 255;
    pixel1[PIXEL_ALPHA] = 255;

    pixel2[PIXEL_RED] = 0;
    pixel2[PIXEL_GREEN] = 0;
    pixel2[PIXEL_BLUE] = 0;
    pixel2[PIXEL_ALPHA] = 0;

    const quint8 *pixelPtrs[2];
    qint16 weights[2];

    pixelPtrs[0] = pixel1;
    pixelPtrs[1] = pixel2;

    weights[0] = 255;
    weights[1] = 0;

    mixOp->mixColors(pixelPtrs, weights, 2, outputPixel);

    QVERIFY((int)outputPixel[PIXEL_RED] == 255);
    QVERIFY((int)outputPixel[PIXEL_GREEN] == 255);
    QVERIFY((int)outputPixel[PIXEL_BLUE] == 255);
    QVERIFY((int)outputPixel[PIXEL_ALPHA] == 255);

    weights[0] = 0;
    weights[1] = 255;

    mixOp->mixColors(pixelPtrs, weights, 2, outputPixel);

    QVERIFY((int)outputPixel[PIXEL_RED] == 0);
    QVERIFY((int)outputPixel[PIXEL_GREEN] == 0);
    QVERIFY((int)outputPixel[PIXEL_BLUE] == 0);
    QVERIFY((int)outputPixel[PIXEL_ALPHA] == 0);

    weights[0] = 128;
    weights[1] = 127;

    mixOp->mixColors(pixelPtrs, weights, 2, outputPixel);

    QVERIFY((int)outputPixel[PIXEL_RED] == 255);
    QVERIFY((int)outputPixel[PIXEL_GREEN] == 255);
    QVERIFY((int)outputPixel[PIXEL_BLUE] == 255);
    QVERIFY((int)outputPixel[PIXEL_ALPHA] == 128);

    pixel1[PIXEL_RED] = 200;
    pixel1[PIXEL_GREEN] = 100;
    pixel1[PIXEL_BLUE] = 50;
    pixel1[PIXEL_ALPHA] = 255;

    pixel2[PIXEL_RED] = 100;
    pixel2[PIXEL_GREEN] = 200;
    pixel2[PIXEL_BLUE] = 20;
    pixel2[PIXEL_ALPHA] = 255;

    mixOp->mixColors(pixelPtrs, weights, 2, outputPixel);

    QVERIFY((int)outputPixel[PIXEL_RED] == 150);
    QCOMPARE((int)outputPixel[PIXEL_GREEN], 150);
    QVERIFY((int)outputPixel[PIXEL_BLUE] == 35);
    QVERIFY((int)outputPixel[PIXEL_ALPHA] == 255);

    pixel1[PIXEL_RED] = 0;
    pixel1[PIXEL_GREEN] = 0;
    pixel1[PIXEL_BLUE] = 0;
    pixel1[PIXEL_ALPHA] = 0;

    pixel2[PIXEL_RED] = 255;
    pixel2[PIXEL_GREEN] = 255;
    pixel2[PIXEL_BLUE] = 255;
    pixel2[PIXEL_ALPHA] = 254;

    weights[0] = 89;
    weights[1] = 166;

    mixOp->mixColors(pixelPtrs, weights, 2, outputPixel);

    QVERIFY((int)outputPixel[PIXEL_RED] == 255);
    QVERIFY((int)outputPixel[PIXEL_GREEN] == 255);
    QVERIFY((int)outputPixel[PIXEL_BLUE] == 255);
    QVERIFY((int)outputPixel[PIXEL_ALPHA] == 165);
}
void KoRgbU8ColorSpaceTester::testMixColorsAverage()
{
    const KoColorSpace* cs = KoColorSpaceRegistry::instance()->rgb8();
    KoMixColorsOp * mixOp = cs->mixColorsOp();

    // Test mixColors.
    quint8 pixel1[4];
    quint8 pixel2[4];
    quint8 outputPixel[4];

    pixel1[PIXEL_RED] = 255;
    pixel1[PIXEL_GREEN] = 255;
    pixel1[PIXEL_BLUE] = 255;
    pixel1[PIXEL_ALPHA] = 255;

    pixel2[PIXEL_RED] = 0;
    pixel2[PIXEL_GREEN] = 0;
    pixel2[PIXEL_BLUE] = 0;
    pixel2[PIXEL_ALPHA] = 0;

    const quint8 *pixelPtrs[2];

    pixelPtrs[0] = pixel1;
    pixelPtrs[1] = pixel2;

    mixOp->mixColors(pixelPtrs, 2, outputPixel);

    QCOMPARE((int)outputPixel[PIXEL_RED], 255);
    QCOMPARE((int)outputPixel[PIXEL_GREEN], 255);
    QCOMPARE((int)outputPixel[PIXEL_BLUE], 255);
    QCOMPARE((int)outputPixel[PIXEL_ALPHA], 128);

    pixel2[PIXEL_ALPHA] = 255;
    mixOp->mixColors(pixelPtrs, 2, outputPixel);

    QCOMPARE((int)outputPixel[PIXEL_RED], 128);
    QCOMPARE((int)outputPixel[PIXEL_GREEN], 128);
    QCOMPARE((int)outputPixel[PIXEL_BLUE], 128);
    QCOMPARE((int)outputPixel[PIXEL_ALPHA], 255);
}

void KoRgbU8ColorSpaceTester::testCompositeOps()
{
    // Just COMPOSITE_COPY for now

    QList<KoID> depthIDs = KoColorSpaceRegistry::instance()->colorDepthList(RGBAColorModelID.id(),
                           KoColorSpaceRegistry::AllColorSpaces);

    Q_FOREACH (const KoID& depthId, depthIDs) {

        if (depthId.id().contains("Float")) continue;

        qDebug() << depthId.id();
        const KoColorSpace* cs = KoColorSpaceRegistry::instance()->colorSpace(
                                     RGBAColorModelID.id(), depthId.id(), "");
        
        const KoCompositeOp* copyOp = cs->compositeOp(COMPOSITE_COPY);
        KoColor src(cs), dst(cs);

        QColor red(255, 0, 0);
        QColor blue(0, 0, 255);
        QColor transparentRed(255, 0, 0, 0);

        // Copying a color over another color should replace the original color
        src.fromQColor(red);
        dst.fromQColor(blue);
        
        qDebug() << src.toQColor() << dst.toQColor();

        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) != 0);

        copyOp->composite(dst.data(), cs->pixelSize(), src.data(), cs->pixelSize(),
                          0, 0, 1, 1, OPACITY_OPAQUE_U8);

        src.fromQColor(red);
        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) == 0);

        // Copying something transparent over something non-transparent should, of course, make the dst transparent
        src.fromQColor(transparentRed);
        dst.fromQColor(blue);

        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) != 0);

        copyOp->composite(dst.data(), cs->pixelSize(), src.data(), cs->pixelSize(),
                          0, 0, 1, 1, OPACITY_OPAQUE_U8);

        src.fromQColor(transparentRed);
        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) == 0);

        // Copying something solid over something transparent
        src.fromQColor(blue);
        dst.fromQColor(transparentRed);

        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) != 0);

        copyOp->composite(dst.data(), cs->pixelSize(), src.data(), cs->pixelSize(),
                          0, 0, 1, 1, OPACITY_OPAQUE_U8);

        src.fromQColor(blue);
        QVERIFY(memcmp(dst.data(), src.data(), cs->pixelSize()) == 0);

    }
}

void KoRgbU8ColorSpaceTester::testCompositeOpsWithChannelFlags()
{
    const KoColorSpace* cs = KoColorSpaceRegistry::instance()->rgb8();
    QList<KoCompositeOp*> ops = cs->compositeOps();

    Q_FOREACH (const KoCompositeOp *op, ops) {
        /**
         * ALPHA_DARKEN composite op doesn't take channel
         * flags into account, so just skip it
         */
        if (op->id() == COMPOSITE_ALPHA_DARKEN) continue;
        if (op->id() == COMPOSITE_DISSOLVE) continue;

        quint8 src[] = {128,128,128,129};
        quint8 goodDst[] = {10,10,10,11};
        quint8 badDst[] = {12,12,12,0};

        KoCompositeOp::ParameterInfo params;
        params.maskRowStart  = 0;
        params.dstRowStride  = 0;
        params.srcRowStride  = 0;
        params.maskRowStride = 0;
        params.rows          = 1;
        params.cols          = 1;
        params.opacity       = 1.0f;
        params.flow          = 1.0f;

        QBitArray channelFlags(4, true);
        channelFlags[2] = false;
        params.channelFlags  = channelFlags;

        params.srcRowStart   = src;

        params.dstRowStart   = goodDst;
        op->composite(params);

        params.dstRowStart   = badDst;
        op->composite(params);

        /**
         * The badDst has zero alpha, so the channels should be zeroed
         * before increasing alpha of the pixel
         */
        if (badDst[3] != 0 && badDst[2] != 0) {
            qDebug() << op->id()
                     << "easy case:" << goodDst[2]
                     << "difficult case:" << badDst[2];

            qDebug() << "The composite op has failed to erase the color "
                "channel which was hidden by zero alpha.";
            qDebug() << "Expected Blue channel:" << 0;
            qDebug() << "Actual Blue channel:  " << badDst[2];

            QFAIL("Failed to erase color channel");
        }
    }
}

#include <QScopedPointer>
#include <KoOptimizedRgbPixelDataScalerU8ToU16Factory.h>
#include <QByteArray>

void KoRgbU8ColorSpaceTester::testScaler()
{
    QScopedPointer<KoOptimizedRgbPixelDataScalerU8ToU16Base> scaler(KoOptimizedRgbPixelDataScalerU8ToU16Factory::create());

    const int numPixels = 31;
    QByteArray srcBytes(1 + numPixels * 4 * sizeof(quint8), 0);
    QByteArray dstBytes(1 + numPixels * 4 * sizeof(quint16), 0);

    const quint8 pattern[] = {0, 128, 192, 255};
    const quint16 expectedDstPattern[] = {0, 32896, 49344, 65535};

    quint8 *unalignedSrcPtr = reinterpret_cast<quint8*>(srcBytes.data() + 1);
    quint8 *unalignedDstPtr = reinterpret_cast<quint8*>(dstBytes.data() + 1);


    for (int i = 0; i < numPixels * 4; i++) {
        unalignedSrcPtr[i] = pattern[i % 4];
    }

    scaler->convertU8ToU16(unalignedSrcPtr, 1, unalignedDstPtr, 1, 1, numPixels);

    const quint8 *srcPtr = reinterpret_cast<const quint8*>(unalignedSrcPtr);
    const quint16 *dstPtr = reinterpret_cast<const quint16*>(unalignedDstPtr);

    for (int i = 0; i < numPixels; i++) {
//        qDebug() << i
//                 << "S" << srcPtr[i * 4 + 0] << srcPtr[i * 4 + 1] << srcPtr[i * 4 + 2] << srcPtr[i * 4 + 3]
//                 << "D" << dstPtr[i * 4 + 0] << dstPtr[i * 4 + 1] << dstPtr[i * 4 + 2] << dstPtr[i * 4 + 3];

        QCOMPARE(dstPtr[i * 4 + 0], expectedDstPattern[0]);
        QCOMPARE(dstPtr[i * 4 + 1], expectedDstPattern[1]);
        QCOMPARE(dstPtr[i * 4 + 2], expectedDstPattern[2]);
        QCOMPARE(dstPtr[i * 4 + 3], expectedDstPattern[3]);
    }

    scaler->convertU16ToU8(unalignedDstPtr, 1, unalignedSrcPtr, 1, 1, numPixels);

    for (int i = 0; i < numPixels; i++) {
//        qDebug() << i
//                 << "S" << srcPtr[i * 4 + 0] << srcPtr[i * 4 + 1] << srcPtr[i * 4 + 2] << srcPtr[i * 4 + 3]
//                 << "D" << dstPtr[i * 4 + 0] << dstPtr[i * 4 + 1] << dstPtr[i * 4 + 2] << dstPtr[i * 4 + 3];

        QCOMPARE(srcPtr[i * 4 + 0], pattern[0]);
        QCOMPARE(srcPtr[i * 4 + 1], pattern[1]);
        QCOMPARE(srcPtr[i * 4 + 2], pattern[2]);
        QCOMPARE(srcPtr[i * 4 + 3], pattern[3]);
    }
}

#include <QByteArray>
#include <kis_debug.h>

class KoIterativeColorMixer
{
public:
    KoIterativeColorMixer(int bucketSize, const KoColorSpace *cs)
        : m_bucketSize(bucketSize),
          m_colorSpace(cs),
          m_buffer(bucketSize * cs->pixelSize(), 0),
          m_weightsBuffer(bucketSize),
          m_totalAverage(cs->pixelSize(), 0),
          m_tempAverage(cs->pixelSize(), 0),
          m_pixelSize(cs->pixelSize()),
          m_mixOp(cs->mixColorsOp())
    {
        m_nextPixelInCurrentBucket = reinterpret_cast<quint8*>(m_buffer.data());
    }

    const quint8 *averagePixel() const {
        return reinterpret_cast<const quint8*>(m_totalAverage.data());
    }

    bool isBucketComplete() const {
        return !m_currentIndexInBucket;
    }

    bool accumulatePixel(quint8 *pixel, qint16 weight)
    {
        //qDebug() << "add" << pixel[0] << pixel[1] << pixel[2];

        memcpy(m_nextPixelInCurrentBucket, pixel, m_pixelSize);
        m_weightsBuffer[m_currentIndexInBucket] = weight;
        m_currentBucketWeightsSum += weight;

        m_nextPixelInCurrentBucket += m_pixelSize;
        m_currentIndexInBucket++;

        const bool bucketComplete = m_currentIndexInBucket == m_bucketSize;

        if (bucketComplete) {
            m_nextPixelInCurrentBucket = reinterpret_cast<quint8*>(m_buffer.data());

            const bool firstBucket = m_currentBucket == 0;

            quint8 *dstAverage = firstBucket ?
                reinterpret_cast<quint8*>(m_totalAverage.data()) :
                reinterpret_cast<quint8*>(m_tempAverage.data());

            m_mixOp->mixColors(m_nextPixelInCurrentBucket,
                               m_weightsBuffer.data(),
                               m_bucketSize,
                               dstAverage,
                               m_currentBucketWeightsSum);

            if (!firstBucket) {
                // we are going to reuse the bucket buffer as a temporary
                // storage for the mixing

                memcpy(m_nextPixelInCurrentBucket, m_totalAverage, m_pixelSize);
                const int weightSum = 16384;
                qint16 bucketWeight =
                    (m_currentBucketWeightsSum * weightSum + (m_currentBucketWeightsSum + m_totalWeightsSum) / 2) /
                    (m_currentBucketWeightsSum + m_totalWeightsSum);
                qint16 totalWeight = weightSum - bucketWeight;

//                qWarning() << "iteration step";
//                qWarning() << "    " << ppVar(bucketWeight);
//                qWarning() << "    " << ppVar(qreal(bucketWeight) / totalWeight);
//                qWarning() << "    " << ppVar(qreal(m_currentBucketWeightsSum) / (m_totalWeightsSum));

//                qWarning() << "    " << ppVar(m_currentBucketWeightsSum);
//                qWarning() << "    " << ppVar(m_totalWeightsSum);
//                qWarning() << "    " << ppVar(m_currentBucket);
//                qWarning() << "    " << ppVar(m_bucketSize);


                if (bucketWeight > 0) {
                    quint8* pixels[] = {reinterpret_cast<quint8*>(m_tempAverage.data()), m_nextPixelInCurrentBucket};
                    qint16 weights[] = {bucketWeight, totalWeight};

                    m_mixOp->mixColors(pixels,
                                       weights,
                                       2,
                                       reinterpret_cast<quint8*>(m_totalAverage.data()),
                                       weightSum);
                } else {
                    KIS_SAFE_ASSERT_RECOVER(!m_currentBucketWeightsSum) {
                        qWarning() << "WARNING: KoIterativeColorMixer has lost precision!";
                        qWarning() << "    " << ppVar(bucketWeight);
                        qWarning() << "    " << ppVar(m_currentBucketWeightsSum);
                        qWarning() << "    " << ppVar(m_totalWeightsSum);
                        qWarning() << "    " << ppVar(m_currentBucket);
                        qWarning() << "    " << ppVar(m_bucketSize);
                    }
                }



            }

//            quint8 *ptr = (quint8*) m_totalAverage.data();
//            qWarning() << ppVar(ptr[0]) << ppVar(ptr[1]) << ppVar(ptr[2]);

            m_totalWeightsSum += m_currentBucketWeightsSum;
            m_currentBucket++;
            m_currentIndexInBucket = 0;
            m_currentBucketWeightsSum = 0;

        }

        return bucketComplete;
    }

private:
    int m_bucketSize = 0;
    const KoColorSpace *m_colorSpace = 0;
    QByteArray m_buffer;
    QVector<qint16> m_weightsBuffer;
    QByteArray m_totalAverage;
    QByteArray m_tempAverage;
    qint64 m_totalWeightsSum = 0;
    int m_currentBucket = 0;
    int m_currentIndexInBucket = 0;
    qint64 m_currentBucketWeightsSum = 0;
    quint8 *m_nextPixelInCurrentBucket = 0;
    const int m_pixelSize = 0;
    KoMixColorsOp *m_mixOp = 0;
};


void KoRgbU8ColorSpaceTester::testIterativeMixing()
{
    const KoColorSpace *cs = KoColorSpaceRegistry::instance()->rgb8();

    qDebug() << ppVar(cs->profile()->name());

    QScopedPointer<KoMixColorsOp::Mixer> mixer(cs->mixColorsOp()->createMixer());

    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < 256; i++) {
            KoColor color(QColor(i, 1, 255 - i), cs);
            qint16 weight = i;
            mixer->accumulate(color.data(), &weight, i, 1);
        }

        KoColor result(Qt::red, cs);
        mixer->computeMixedColor(result.data());

        qDebug() << "xxx" << k << result.data()[0] << result.data()[1] << result.data()[2];
    }


#if 0

    KoIterativeColorMixer mixer(16, cs);

    for (int k = 0; k < 100; k++) {
        for (int i = 0; i < 256; i++) {
            KoColor color(QColor(i, 1, 255 - i), cs);
            mixer.accumulatePixel(color.data(), i);
        }

        QVERIFY(mixer.isBucketComplete());
        qDebug() << "xxx" << mixer.averagePixel()[0] << mixer.averagePixel()[1] << mixer.averagePixel()[2];
        QVERIFY(mixer.isBucketComplete());
    }
#endif
#if 0
    {
        qreal errorPortion = 0.001;

        qreal x = 1.0986;
        const qreal tolerance = x * errorPortion;



        qreal integral = std::floor(x);
        qreal fractional = x - integral;

        qreal reciprocal = 1.0 / fractional;


    }
#endif
}




KISTEST_MAIN(KoRgbU8ColorSpaceTester)
