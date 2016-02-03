#include "detector_hog.hpp"
using namespace std;
using namespace cv;

DetectorHOG::DetectorHOG(vector<string>argumentos_nombre, vector<string>argumentos_valor)
{
	this->nombre = "DetectorHOG";
	unsigned int n = argumentos_nombre.size();
	if( n != cantidad_de_argumentos )
	{
		//error
	}

	unsigned int j = 0;
	for( unsigned int i = 0 ; i < n ; i++ )
	{
		if( argumentos_nombre.at(i) == "pasoEscala")
		{
			this->pasoEscala = stod(argumentos_valor.at(i));
			j++;
		}

		if( argumentos_nombre.at(i) == "umbralAgrupamiento")
		{
			this->umbralAgrupamiento = stoi(argumentos_valor.at(i),nullptr,10);
			j++;
		}

		if( argumentos_nombre.at(i) == "setSVMDetector")
		{
			this->setSVMDetector = argumentos_valor.at(i);
			j++;
		}

	}
	if( j != n ) // No se cargaron todos los parámetros
	{
		// Error? Podrían tener valores por defecto. O comprobar solo algunos.
	}

//    CV_WRAP HOGDescriptor() : winSize(64,128), blockSize(16,16), blockStride(8,8),
//        cellSize(8,8), nbins(9), derivAperture(1), winSigma(-1),
//        histogramNormType(HOGDescriptor::L2Hys), L2HysThreshold(0.2), gammaCorrection(true),
//        nlevels(HOGDescriptor::DEFAULT_NLEVELS)
//    {}

	Size winSize;	// Depende del modelo entrenado
	if(setSVMDetector == "getDefaultPeopleDetector")
		winSize = Size(64,128);
	else if (setSVMDetector == "getDaimlerPeopleDetector")
		winSize = Size(48,96);
	else
	{
		cout << "\nSVMDetector inválido. Debe ser getDefaultPeopleDetector o getDaimlerPeopleDetector\n"
				"Se usará getDefaultPeopleDetector\n";
		winSize = Size(64,128);
	}

	//Size winSize=Size(64, 128);	// Depende del modelo entrenado
	Size blockSize = Size(16,16);	// Solo 16*16 soportado
	Size blockStride = Size(8,8);	// Múltiplo de cellSize
	Size cellSize = Size(8,8);	// Solo 8*8 soportado
	int nbins = 9;	// Solo 9 soportado
	int derivAperture = 1;	// ?
	double winSigma =-1;	// Gaussian smoothing window parameter. (-1 por defecto)
	int histogramNormType = HOGDescriptor::L2Hys;
	double L2HysThreshold = 0.2;
	bool gammaCorrection = true;
	int nlevels = HOGDescriptor::DEFAULT_NLEVELS;

	hog = HOGDescriptor(winSize, blockSize, blockStride, cellSize, nbins, derivAperture, winSigma,
			histogramNormType, L2HysThreshold, gammaCorrection, nlevels);

	// El detector getDefaultPeopleDetector viene hardcodeado en hog.cpp de opencv. También está
	// getDaimlerPeopleDetector, pero para ventanas de 48*96
	if(setSVMDetector == "getDefaultPeopleDetector")
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	else if (setSVMDetector == "getDaimlerPeopleDetector")
		hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
	else
	{
		cout << "\nSVMDetector inválido. Debe ser getDefaultPeopleDetector o getDaimlerPeopleDetector\n"
				"Se usará getDefaultPeopleDetector\n";
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	}


//    virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
//                                  double hitThreshold=0, Size winStride=Size(),
//                                  Size padding=Size(), double scale=1.05,
//                                  double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;


	parametros_nombre.push_back("pasoEscala");
	parametros_valor.push_back(to_string(pasoEscala));
	parametros_nombre.push_back("umbralAgrupamiento");
	parametros_valor.push_back(to_string(umbralAgrupamiento));
	parametros_nombre.push_back("setSVMDetector");
	parametros_valor.push_back(setSVMDetector);

}

DetectorHOG::~DetectorHOG()
{
}

void DetectorHOG::detectar(const Mat& i_img,  vector<struct_resultados>& i_res)
{
//	 C++: void gpu::HOGDescriptor::detectMultiScale(const GpuMat& img, vector<Rect>& found_locations, double hit_threshold=0, Size win_stride=Size(), Size padding=Size(), double scale0=1.05, int group_threshold=2)
//	    Parameters:
//
//	        img – Source image. See gpu::HOGDescriptor::detect() for type limitations.
//	        found_locations – Detected objects boundaries.
//	        hit_threshold – Threshold for the distance between features and SVM classifying plane. See gpu::HOGDescriptor::detect() for details.
//	        win_stride – Window stride. It must be a multiple of block stride.
//	        padding – Mock parameter to keep the CPU interface compatibility. It must be (0,0).
//	        scale0 – Coefficient of the detection window increase.
//	        group_threshold – Coefficient to regulate the similarity threshold. When detected, some objects can be covered by many rectangles. 0 means not to perform grouping. See groupRectangles() .

	//    virtual void detectMultiScale(const Mat& img, CV_OUT vector<Rect>& foundLocations,
	//                                  double hitThreshold=0, Size winStride=Size(),
	//                                  Size padding=Size(), double scale=1.05,
	//                                  double finalThreshold=2.0, bool useMeanshiftGrouping = false) const;

	if( i_img.depth() != CV_8U && i_img.depth() != CV_8S )
	{
		cout << "\nHOGDescriptor solo soporta 8 bits\n";
		/// TODO: Error
		return;
	}



	Mat con_detecciones = i_img.clone();
	struct_resultados aux_res;

    vector<Rect> found, found_filtered;
    double t = (double)getTickCount();
    // run the detector with default parameters. to get a higher hit-rate
    // (and more false alarms, respectively), decrease the hitThreshold and
    // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
    // hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);

    hog.detectMultiScale(i_img, found, 0, Size(8,8), Size(), pasoEscala , umbralAgrupamiento);
    t = (double)getTickCount() - t;

    //printf("tdetection time = %gms\n", t*1000./cv::getTickFrequency());
//    for( auto i: found)
//    	cout << "\nFound = " << i << endl;

    // Esta parte..qué hace?
    size_t i, j;
    for( i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];
        for( j = 0; j < found.size(); j++ )
            if( j != i && (r & found[j]) == r)
                break;
        if( j == found.size() )
            found_filtered.push_back(r);
    }

//    for( auto i: found_filtered)
//    	cout << "\nFound_filtered = " << i << endl;

    for( i = 0; i < found_filtered.size(); i++ )
    {
        Rect r = found_filtered[i];
        // the HOG detector returns slightly larger rectangles than the real objects.
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);



        // A struct_resultados
        rect_a_struct_resultados(r,aux_res);
        aux_res.tiempo = t*1000./cv::getTickFrequency();

		if( i_img.depth() == CV_8U || i_img.depth() == CV_8S ) // Actualmente hog solo soporta 8...
			aux_res.prof = 8;
		else
			aux_res.prof = 16;

        i_res.push_back(aux_res);



        // Show
        if( mostrar_detecciones )
        {
            rectangle(con_detecciones, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
        }
    }
    if( mostrar_detecciones )
    {
    	namedWindow("Detecciones", CV_WINDOW_KEEPRATIO | CV_WINDOW_NORMAL);
    	imshow("Detecciones", con_detecciones);
    	waitKey(0);
    }
//
//	for( int i = 0 ; i < 3 ; i++) // Simulamos 3 detecciones.
//	{
//		struct_resultados aux;
//
//		aux.aba_der_x = 1;
//		aux.aba_der_y = 2;
//		aux.aba_izq_x = 3;
//		aux.aba_izq_y = 4;
//		aux.arr_der_x = 5;
//		aux.arr_der_y = 6;
//		aux.arr_izq_x = 7;
//		aux.arr_izq_y = 8;
//		aux.comp = 1;
//		//aux.img = 4;
//		aux.prof = 8;
//		//aux.set = 1;
//		aux.tiempo = 222;
//		i_res.push_back(aux);
//	}

	return;
}


 