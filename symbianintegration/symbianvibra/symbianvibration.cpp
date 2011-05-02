#include "symbianvibration.h"
#include <QLatin1Literal>

namespace Symbian
{
using namespace qutim_sdk_0_3;

Vibration::Vibration() : m_vibra(CHWRMVibra::NewL())
{
}

Vibration::~Vibration()
{
	delete m_vibra;
}

void Vibration::handleNotification(qutim_sdk_0_3::Notification *notification)
{
	Q_UNUSED(notification);
	// Think about better value
	m_vibra->StartVibraL(300);
}

} //namespace Symbian
