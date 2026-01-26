class IAligner {
    public:
        virtual AlignmentResult align(
            const std::string& a,
            const std::string& b
        ) = 0;

        virtual std::string name () const = 0;
        virtual ~IAligner() = default;
};