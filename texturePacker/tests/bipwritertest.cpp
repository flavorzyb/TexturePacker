#include "bipwritertest.h"
#include "common/include/fileutils.h"
#include "common/include/pvr.h"
#include "common/include/etc.h"
BipWriterTest::BipWriterTest()
{
}

void BipWriterTest::init()
{
}

void BipWriterTest::cleanup()
{
}

void BipWriterTest::testSavePVR()
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

    pvr->setImageVO(ivo);

    pvr->load();
    BipWriter pvrWriter(pvr);
    QCOMPARE(pvrWriter.save("output/zw_shu.bip"), true);

    PVR *pvrFail = new PVR();
    BipWriter writerFail(pvrFail);
    QCOMPARE(writerFail.save("output/zw_shu_fail.bip"), false);
}

void BipWriterTest::testSaveETC()
{
    ETC * etc = new ETC("images/zw_shu.pkm");
    ImageVO ivo(500, 500);
    ivo.setFileName("zw_shu.pkm");

    FrameVO fvo(500, 500);
    fvo.setName("zw_shu.pkm");
    fvo.setMd5String(FileUtils::md5File("images/zw_shu.pvr"));
    fvo.setRect(0, 0, 500, 500);
    fvo.setOffset(0, 0);
    fvo.setRotated(false);
    fvo.setSourceColorRect(0, 0, 500, 500);

    ivo.addFrame(fvo);

    etc->setImageVO(ivo);

    etc->load();
    BipWriter pvrWriter(etc);
    QCOMPARE(pvrWriter.save("output/zw_shu_etc.bip"), true);

    ETC *etcFail = new ETC();
    BipWriter writerFail(etcFail);
    QCOMPARE(writerFail.save("output/zw_shu_etc_fail.bip"), false);
}
