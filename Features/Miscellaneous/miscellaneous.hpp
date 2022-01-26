#pragma once
Vector2 Pitch, Yaw;


namespace Misc {
	void DoMisc(BasePlayer* localPlayer) {
		if (Config::bFakeAdmin)
			localPlayer->SetFlag(Unity::PlayerFlags::IsAdmin);
		
		if (localPlayer->GetActiveItem()->GetRecoilMM(Pitch, Yaw))
			localPlayer->GetActiveItem()->GetBaseProjectile()->GetRecoilProperties()->SetRecoilProperties(Pitch, Yaw, Config::fRecoilPercent);
		
	}
}