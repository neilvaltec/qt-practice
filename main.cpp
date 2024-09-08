#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QStandardPaths>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Main widget
    QWidget mainWidget;
    QVBoxLayout *layout = new QVBoxLayout(&mainWidget);

    // Video widget
    QVideoWidget *videoWidget = new QVideoWidget;
    layout->addWidget(videoWidget);

    // Media player
    QMediaPlayer *player = new QMediaPlayer;
    player->setVideoOutput(videoWidget);

    // Control buttons
    QPushButton *playButton = new QPushButton("Play");
    QPushButton *pauseButton = new QPushButton("Pause");
    QPushButton *stopButton = new QPushButton("Stop");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(playButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(stopButton);
    layout->addLayout(buttonLayout);

    // Connect buttons to player
    QObject::connect(playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    QObject::connect(pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    QObject::connect(stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);

    // Volume slider
    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(player->volume());
    layout->addWidget(new QLabel("Volume"));
    layout->addWidget(volumeSlider);

    // Connect volume slider to player
    QObject::connect(volumeSlider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);

    // Video property sliders
    QSlider *brightnessSlider = new QSlider(Qt::Horizontal);
    QSlider *contrastSlider = new QSlider(Qt::Horizontal);
    QSlider *hueSlider = new QSlider(Qt::Horizontal);
    QSlider *saturationSlider = new QSlider(Qt::Horizontal);

    layout->addWidget(new QLabel("Brightness"));
    layout->addWidget(brightnessSlider);
    layout->addWidget(new QLabel("Contrast"));
    layout->addWidget(contrastSlider);
    layout->addWidget(new QLabel("Hue"));
    layout->addWidget(hueSlider);
    layout->addWidget(new QLabel("Saturation"));
    layout->addWidget(saturationSlider);

    // Connect video property sliders
    QObject::connect(brightnessSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setBrightness);
    QObject::connect(videoWidget, &QVideoWidget::brightnessChanged, brightnessSlider, &QSlider::setValue);

    QObject::connect(contrastSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setContrast);
    QObject::connect(videoWidget, &QVideoWidget::contrastChanged, contrastSlider, &QSlider::setValue);

    QObject::connect(hueSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setHue);
    QObject::connect(videoWidget, &QVideoWidget::hueChanged, hueSlider, &QSlider::setValue);

    QObject::connect(saturationSlider, &QSlider::sliderMoved, videoWidget, &QVideoWidget::setSaturation);
    QObject::connect(videoWidget, &QVideoWidget::saturationChanged, saturationSlider, &QSlider::setValue);

    // Fullscreen toggle button
    QPushButton *fullscreenButton = new QPushButton("Toggle Fullscreen");
    layout->addWidget(fullscreenButton);

    QObject::connect(fullscreenButton, &QPushButton::clicked, [videoWidget]() {
        if (videoWidget->isFullScreen()) {
            videoWidget->setFullScreen(false);
        } else {
            videoWidget->setFullScreen(true);
        }
    });

    // Set up playlist
    QMediaPlaylist *playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);

    // Add a button to open files
    QPushButton *openButton = new QPushButton("Open File");
    layout->addWidget(openButton);

    // Connect the open button to a file dialog
    QObject::connect(openButton, &QPushButton::clicked, [&]() {
        QString fileName = QFileDialog::getOpenFileName(&mainWidget,
            QObject::tr("Open Media"), 
            QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0),
            QObject::tr("Media Files (*.mp4 *.avi *.mkv *.mp3 *.wav)"));

        if (!fileName.isEmpty()) {
            playlist->addMedia(QUrl::fromLocalFile(fileName));
            if (playlist->mediaCount() == 1) {
                playlist->setCurrentIndex(0);
                player->play();
            }
        }
    });

    // Set the playlist mode (optional)
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    mainWidget.setWindowTitle("Qt Media Player");
    mainWidget.resize(800, 600);
    mainWidget.show();

    return app.exec();
}