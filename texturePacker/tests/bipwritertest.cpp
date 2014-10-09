#include "bipwritertest.h"

BipWriterTest::BipWriterTest()
{
}

void BipWriterTest::init()
{
    PVR * pvr = new PVR("images/zw_shu.pvr");
    ImageVO ivo(500, 500);
    ivo.setFileName("zw_shu.pvr");
    ivo.setRect(2, 2, 428, 412);
    ivo.setOffset(25, 22);
    ivo.setRotated(false);
    ivo.setSourceColorRect(61, 22, 428, 412);
    ivo.setSize(512, 512);
    pvr->setImagevo(ivo);
    pvr->load();
    m_writer = new BipWriter(pvr);
}

void BipWriterTest::cleanup()
{
    delete m_writer;
}

void BipWriterTest::testSave()
{
    QCOMPARE(m_writer->save("output/zw_shu.bip"), true);

    PVR *pvr = new PVR();
    BipWriter writer(pvr);
    QCOMPARE(writer.save("output/zw_shu.bip"), false);
}
