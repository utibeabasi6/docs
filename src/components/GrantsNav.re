module SideNav = {
  module Styles = {
    open Css;
    let container =
      style([
        display(`none),
        media(Theme.MediaQuery.desktop, [display(`block)]),
      ]);

    let sideNav = sticky =>
      style([
        display(`none),
        position(sticky ? `fixed : `absolute),
        top(sticky ? `rem(3.5) : `rem(152.)),
        marginLeft(`calc((`sub, `vw(50.), `rem(71. /. 2.)))),
        width(`rem(14.)),
        zIndex(100),
        background(white),
        media(Theme.MediaQuery.desktop, [display(`block)]),
      ]);
  };

  [@react.component]
  let make = (~children) => {
    let router = Next.Router.useRouter();
    let hashExp = Js.Re.fromString("#(.+)");
    let scrollTop = Hooks.useScroll();
    let calcHash = path =>
      Js.Re.(exec_(hashExp, path) |> Option.map(captures))
      |> Js.Option.andThen((. res) => Js.Nullable.toOption(res[0]))
      |> Js.Option.getWithDefault("");
    let (hash, setHash) = React.useState(() => calcHash(router.asPath));

    React.useEffect(() => {
      let handleRouteChange = url => setHash(_ => calcHash(url));
      router.events
      ->Next.Router.Events.on("hashChangeStart", handleRouteChange);
      Some(
        () =>
          router.events
          ->Next.Router.Events.off("hashChangeStart", handleRouteChange),
      );
    });

    <SideNav currentSlug=hash className={Styles.sideNav(scrollTop > 2400)}>
      children
    </SideNav>;
  };
};

module Dropdown = {
  module Styles = {
    open Css;

    let container =
      style([
        position(`sticky),
        display(`block),
        top(`rem(2.)),
        marginTop(`rem(4.)),
        zIndex(100),
        media(Theme.MediaQuery.desktop, [display(`none)]),
      ]);
  };

  module Item = DropdownNav.Item;
  module Section = DropdownNav.Section;

  [@react.component]
  let make = () => {
    let router = Next.Router.useRouter();
    let hashExp = Js.Re.fromString("#(.+)");
    let calcHash = path =>
      Js.Re.(exec_(hashExp, path) |> Option.map(captures))
      |> Js.Option.andThen((. res) => Js.Nullable.toOption(res[0]))
      |> Js.Option.getWithDefault("");
    let (hash, setHash) = React.useState(() => calcHash(router.asPath));

    React.useEffect(() => {
      let handleRouteChange = url => setHash(_ => calcHash(url));
      router.events
      ->Next.Router.Events.on("hashChangeStart", handleRouteChange);
      Some(
        () =>
          router.events
          ->Next.Router.Events.off("hashChangeStart", handleRouteChange),
      );
    });

    <div className=Styles.container>
      <Wrapped>
        <DropdownNav currentSlug=hash defaultValue="Grants">
          <Item title="Product / Front-end Projects" slug="#frontend" />
          <Item title="Protocol Projects" slug="#protocol" />
          <Item
            title="Opening Marketing and Community Projects"
            slug="#marketing-community"
          />
          <Item title="How to Apply" slug="#how-to-apply" />
          <Item title="Contributers" slug="#contributors" />
          <Item title="FAQ" slug="#faq" />
        </DropdownNav>
      </Wrapped>
    </div>;
  };
};