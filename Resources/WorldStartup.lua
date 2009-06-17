function WorldStartup()
	Print( "World started up!" );
	localplayer= World:GetLocalPlayerEntity();
	localplayer:SetLookVector( Vector(0.0, 0.0, -1.0) );
	localplayer:SetVelocity( Vector(0.0, 0.0, -0.001) );
	return 1;
end
