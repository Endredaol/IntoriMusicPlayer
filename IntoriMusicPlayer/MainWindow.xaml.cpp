#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "winrt/Microsoft.UI.Input.h"
#include "winrt/Microsoft.UI.Composition.SystemBackdrops.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Media;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Windowing;
using namespace Microsoft::UI::Composition::SystemBackdrops;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::IntoriMusicPlayer::implementation
{
	MainWindow::MainWindow()
	{
		InitializeComponent();

		InitializeSystemBackdrop();

		MaterialComboBox().SelectedIndex(0);

		this->Closed({ this,&MainWindow::OnClose });
	}


	void MainWindow::InitializeSystemBackdrop()
	{
		m_configurationSource = SystemBackdropConfiguration();
		m_configurationSource.IsInputActive(true);

		if (MicaController::IsSupported()) { SetBackdropController<MicaController>(MicaKind::Base); }
	}

	template<typename T, typename U>
	void MainWindow::SetBackdropController(U kind)
	{
		auto controller = T();

		if constexpr (std::is_same_v<T, MicaController>) { controller.Kind(kind); }
		else if constexpr (std::is_same_v<T, DesktopAcrylicController>) { controller.Kind(kind); }

		controller.SetSystemBackdropConfiguration(m_configurationSource);
		controller.AddSystemBackdropTarget(this->try_as<winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop>());

		m_backdropController = controller;
		m_isMica = std::is_same_v<T, MicaController>;
	}

	void MainWindow::MaterialSelectionComboBox(IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const&)
	{
		auto comboBox = sender.as<ComboBox>();
		auto selectedItem = comboBox.SelectedItem().as<ComboBoxItem>();
		auto material = selectedItem.Tag().as<hstring>();

		if (material == L"Mica") { if (MicaController::IsSupported()) { SetBackdropController<MicaController>(MicaKind::Base); } }
		else if (material == L"MicaAlt") { if (MicaController::IsSupported()) { SetBackdropController<MicaController>(MicaKind::BaseAlt); } }
		else if (material == L"Acrylic") { if (DesktopAcrylicController::IsSupported()) { SetBackdropController<DesktopAcrylicController>(DesktopAcrylicKind::Default); } }
		else if (material == L"AcrylicBase") { if (DesktopAcrylicController::IsSupported()) { SetBackdropController<DesktopAcrylicController>(DesktopAcrylicKind::Base); } }
		else if (material == L"AcrylicThin") { if (DesktopAcrylicController::IsSupported()) { SetBackdropController<DesktopAcrylicController>(DesktopAcrylicKind::Thin); } }
	}

	void MainWindow::OnClose(IInspectable const&, IInspectable const&)
	{
		if (m_backdropController) { m_backdropController = nullptr; }
	}
}
