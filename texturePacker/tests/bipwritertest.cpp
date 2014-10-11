#include "bipwritertest.h"
#include "common/include/fileutils.h"

BipWriterTest::BipWriterTest()
{
}

void BipWriterTest::init()
{
    PVR * pvr = new PVR("images/zw_shu.pvr");
    ImageVO ivo(512, 512);
    ivo.setFileName("zw_shu.pvr");

    FrameVO fvo(500, 500);
    fvo.setName("zw_shu.pvr");
    fvo.setMd5String(FileUtils::md5File("images/zw_shu.pvr"));
    fvo.setRect(2, 2, 428, 412);
    fvo.setOffset(25, 22);
    fvo.setRotated(false);
    fvo.setSourceColorRect(61, 22, 428, 412);

    ivo.addFrame(fvo);

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
