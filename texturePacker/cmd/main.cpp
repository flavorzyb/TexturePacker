#include <QCoreApplication>
#include "common/include/publisher.h"

int main(int argc, char *argv[])
{
    SettingsVO svo;
    svo.setInputPath(svo.tr("input"));
    svo.setOutputPath(svo.tr("output"));
    svo.setFormat(SettingsVO::ANDROID);

    Publisher pub(svo);
    printf("input:%s output:%s formate:%d\n",
           pub.getSettingsVO().getInputPath().toStdString().c_str(),
           pub.getSettingsVO().getOutputPath().toStdString().c_str(),
           (pub.getSettingsVO().getFormat() == SettingsVO::ANDROID) ? "android" : "ios");

    printf("this is a cmd application\n");
    return 0;
}
