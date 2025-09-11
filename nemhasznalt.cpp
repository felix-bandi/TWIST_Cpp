/*void MainWindow::ARC_rajzol()
{
	int i = ARC_vector.size() - 1;
	pFactory->CreatePathGeometry(&ARC_vector[i].pg);
	ID2D1GeometrySink* pSink;
	ARC_vector[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	ak.x = ARC_vector[i].xk;
	ak.y = ARC_vector[i].yk;
	av.x = ARC_vector[i].xv;
	av.y = ARC_vector[i].yv;
	meret.width = ARC_vector[i].rx;
	meret.height = ARC_vector[i].ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, ARC_vector[i].i, ARC_vector[i].s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/

/*void MainWindow::ARC_rajzol(std::vector<ARC>& ARC)
{
	if (ARC.empty()) return;
	size_t i = ARC.size() - 1;

	ComPtr<ID2D1PathGeometry> pg;
	if (FAILED(pFactory->CreatePathGeometry(&pg))) return;

	ComPtr<ID2D1GeometrySink> sink;
	if (FAILED(pg->Open(&sink))) return;

	sink->SetFillMode(D2D1_FILL_MODE_WINDING);

	const auto startPt = D2D1::Point2F(ARC[i].xk, ARC[i].yk);
	const auto endPt = D2D1::Point2F(ARC[i].xv, ARC[i].yv);
	const auto arcSize = D2D1::SizeF(ARC[i].rx, ARC[i].ry);
	sink->BeginFigure(startPt, D2D1_FIGURE_BEGIN_HOLLOW);
	sink->AddArc(D2D1::ArcSegment(endPt, arcSize, 0.0f, ARC[i].i, ARC[i].s));
	sink->EndFigure(D2D1_FIGURE_END_OPEN);
	if (FAILED(sink->Close())) return;

	ARC[i].pg = pg.Detach();
}*/

/*void MainWindow::ARC_rajzol_betölt()
{
	int i = ARC_betölt.size() - 1;
	pFactory->CreatePathGeometry(&ARC_betölt[i].pg);
	ID2D1GeometrySink* pSink;
	ARC_betölt[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	ak.x = ARC_betölt[i].xk;
	ak.y = ARC_betölt[i].yk;
	av.x = ARC_betölt[i].xv;
	av.y = ARC_betölt[i].yv;
	meret.width = ARC_betölt[i].rx;
	meret.height = ARC_betölt[i].ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, ARC_betölt[i].i, ARC_betölt[i].s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/

/*void MainWindow::ARC_rajzol_2()
{
	SafeRelease(&pPathGeometry_2);
	pFactory->CreatePathGeometry(&pPathGeometry_2);
	ID2D1GeometrySink* pSink;
	pPathGeometry_2->Open(&pSink);
	ak.x = arc.xk;
	ak.y = arc.yk;
	arc.vsz = atan2((arc.kpx - xx), (arc.kpy - yy));
	if (arc.i == D2D1_SWEEP_DIRECTION_CLOCKWISE) { szt = arc.ksz - arc.vsz; }
	else { szt = arc.vsz - arc.ksz; }
	if (szt < 0) szt += 2 * M_PI;
	if (szt <= M_PI) { arc.s = D2D1_ARC_SIZE_SMALL; }
	else if (szt > M_PI) { arc.s = D2D1_ARC_SIZE_LARGE; }
	av.x = arc.kpx - sin(arc.vsz) * arc.rx;
	av.y = arc.kpy - cos(arc.vsz) * arc.ry;
	meret.width = arc.rx;
	meret.height = arc.ry;
	pSink->BeginFigure(ak, D2D1_FIGURE_BEGIN_HOLLOW);
	pSink->AddArc(D2D1::ArcSegment(av, meret, 0.0, arc.i, arc.s));
	pSink->EndFigure(D2D1_FIGURE_END_OPEN);
	pSink->Close();
	SafeRelease(&pSink);
}*/

/*void MainWindow::POLIGON_rajzol_betölt()
{
	int i = POLIGON_betölt.size() - 1;
	for (int j = 0; j < POLIGON_betölt[i].pont.size(); j++) pontok[j] = POLIGON_betölt[i].pont[j];
	pFactory->CreatePathGeometry(&POLIGON_betölt[i].pg);
	ID2D1GeometrySink* pSink;
	POLIGON_betölt[i].pg->Open(&pSink);
	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
	pSink->BeginFigure(POLIGON_betölt[i].pont[0], D2D1_FIGURE_BEGIN_FILLED);
	pSink->AddLines(pontok, POLIGON_betölt[i].pont.size());
	pSink->AddLine(POLIGON_betölt[i].pont[0]);
	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	pSink->Close();
	SafeRelease(&pSink);
}*/